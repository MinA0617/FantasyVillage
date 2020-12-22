#include "MapCreator.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "Resource/M3ResourceManager.h"
#include "ModelCenter/Map/WorldMap.h"
#include "ModelCenter/Map/MapManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Resource/M3ResourceManager.h"
#include "Engine/StaticMesh.h"
#include "ModelCenter/Character/CharacterManager.h"

UMapCreator::UMapCreator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentCubeIndex = 0;
	CurrentRotation = 0;
}

bool UMapCreator::SetActivation(bool bIsActivation)
{
	UM3GameInstance::GetPC()->HelperComponent.HelperMesh->SetHiddenInGame(bIsActivation);
	if (HelperActor == nullptr && bIsActivation)
	{
		HelperActor = UM3GameInstance::GetPC()->GetWorld()->SpawnActor<ACreatingHelperActor>();
	}
	HelperActor->SetActorHiddenInGame(!bIsActivation);
	SetCubeMeshActivation(bIsActivation);
	if (bIsActivation)
	{
		TArray<FInstallationItemSlot>& InstallationItemList = UM3GameInstance::GetCharacterManager()->Inventory->InstallationItemList;
		if (InstallationItemList.Num() == 0)
		{
			SetActivation(false);
			return false;
		}
		if (InventoryIndex < InstallationItemList.Num())
		{
			if (CurrentCubeIndex != InstallationItemList[InventoryIndex].Item->DefaultInfo.ID)
			{
				for (int i = 0; i < InstallationItemList.Num(); i++)
				{
					if (CurrentCubeIndex == InstallationItemList[InventoryIndex].Item->DefaultInfo.ID)
					{
						InventoryIndex = i;
						SetCubeIndex(InventoryIndex);
						return true;
					}
				}
				InventoryIndex = 0;
				CurrentCubeIndex = InstallationItemList[InventoryIndex].Item->DefaultInfo.ID;
				SetCubeIndex(InventoryIndex);
			}
		}
	}
	
	return true;
}

void UMapCreator::SetCubeMeshActivation(bool bIsActivation)
{
	UM3GameInstance::GetPC()->HelperComponent.ObjectMesh->SetHiddenInGame(!bIsActivation);
}

void UMapCreator::SetNextIndex(bool IsNext)
{
	if (IsNext && InventoryIndex + 1 < UM3GameInstance::GetCharacterManager()->Inventory->InstallationItemList.Num())
	{
		SetCubeIndex(InventoryIndex + 1);
	}
	else if (!IsNext && InventoryIndex - 1 >= 0)
	{
		SetCubeIndex(InventoryIndex - 1);
	}
}

void UMapCreator::SetCubeIndex(int Index)
{ 
	InventoryIndex = Index;
	int NewCubeIndex = UM3GameInstance::GetCharacterManager()->Inventory->InstallationItemList[Index].Item->DefaultInfo.ID;
	CurrentCubeIndex = NewCubeIndex;
	FCubeTableResource* CubeTableRow = UM3GameInstance::GetMapManager()->CubeDataTable->FindRow<FCubeTableResource>(FName(*(FString::FromInt(CurrentCubeIndex))), TEXT("z"));
	check(CubeTableRow);
	UM3GameInstance::GetResourceManager()->GetAsyncObjectFromID(CubeTableRow->ResourceID, FStreamableDelegate::CreateUObject(this, &UMapCreator::SetCubeMesh));
	HelperActor->CurrentIndex = CurrentCubeIndex;
	HelperActor->SetDependency(UM3GameInstance::GetMapManager()->GetInstanceActor(CurrentCubeIndex)->DependencyList[CurrentRotation]);
}

void UMapCreator::SetCubeMesh()
{
	FCubeTableResource* CubeTableRow = UM3GameInstance::GetMapManager()->CubeDataTable->FindRow<FCubeTableResource>(FName(*(FString::FromInt(CurrentCubeIndex))), TEXT("z"));
	check(CubeTableRow);
	UStaticMesh* Mesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(CubeTableRow->ResourceID);
	HelperActor->SetCubeMesh(Mesh);
	UM3GameInstance::GetPC()->HelperComponent.ObjectMesh->SetStaticMesh(Mesh);
}

void UMapCreator::SetRotation(int Rotation)
{
	CurrentRotation = Rotation;
	HelperActor->SetDependency(UM3GameInstance::GetMapManager()->GetInstanceActor(CurrentCubeIndex)->DependencyList[CurrentRotation]);
}

bool UMapCreator::CreateCube()
{
	bool Result = UM3GameInstance::GetMapManager()->CreateCube(CurrentCubeIndex, HelperActor->GetActorLocation(), CurrentRotation);
	UM3GameInstance::GetCharacterManager()->Inventory->RemoveItem(EItemType::INSTALLATION, InventoryIndex);
	if (InventoryIndex >= UM3GameInstance::GetCharacterManager()->Inventory->InstallationItemList.Num())
	{
		InventoryIndex = UM3GameInstance::GetCharacterManager()->Inventory->InstallationItemList.Num() - 1;
	}
	SetCubeIndex(InventoryIndex);
	return Result;
}