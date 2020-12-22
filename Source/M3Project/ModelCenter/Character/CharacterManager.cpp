#include "CharacterManager.h"
#include "ConstructorHelpers.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Map/MapManager.h"
#include "GameHandler/M3GameMode.h"
#include "ModelCenter/Object/ActorManager/Factory/CommandFactory.h"
#include "ModelCenter/Object/ActorManager/ActorManager.h"

UCharacterManager::UCharacterManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FString MonsterDataPath = TEXT("DataTable'/Game/Resource/ResourceTable/MonsterTable.MonsterTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_Monster(*MonsterDataPath);
	if (DT_Monster.Succeeded()) MonsterTable = DT_Monster.Object;

	Inventory = ObjectInitializer.CreateDefaultSubobject<UInventory>(this, TEXT("Inventory"));
}

void UCharacterManager::LoadZoneNPC(int PosX, int PosY)
{
	FVector Pos = FVector();
	for (int i = 0; i < NPCDataList[PosX][PosY].Num(); i++)
	{
		NPCData& Data = NPCDataList[PosX][PosY][i];
		if (IsMonster(Data.Index))
		{
			if (UM3GameInstance::GetMapManager()->GetEmptyPos(Pos, PosX, PosY, Data.PosX, Data.PosY))
			{
				CCommandFactory::AddNPCCommand(NPCList[PosX][PosY], Pos, Data.Index);
			}
		}
		else
		{
			if (UM3GameInstance::GetMapManager()->GetEmptyPos(Pos, PosX, PosY, Data.PosX, Data.PosY, Data.PosZ))
			{
				CCommandFactory::AddNPCCommand(NPCList[PosX][PosY], Pos, Data.Index);
			}
		}
	}
}

void UCharacterManager::RemoveZoneNPC(int PosX, int PosY)
{
	for (int i = 0; i < NPCList[PosX][PosY].Num(); i++)
	{
		NPCList[PosX][PosY][i]->Destroy();
	}
	NPCList[PosX][PosY].Empty();
}

AMonsterCharacter* UCharacterManager::SpawnMonster(FVector pos, int id)
{
	FMonsterTableResource* Data = MonsterTable->FindRow<FMonsterTableResource>(FName(*(FString::FromInt(id))), TEXT("z"));
	if (Data == nullptr) return nullptr;
	AMonsterCharacter* Monster = AM3GameMode::GetInstance()->GetWorld()->SpawnActor<AMonsterCharacter>(pos, FRotator::ZeroRotator);
	if (Monster == nullptr) return nullptr;
	Monster->SetActorLocation(pos, false, (FHitResult*)nullptr, ETeleportType::TeleportPhysics);
	Monster->MonsterInfo.ID = id;
	Monster->BuildMonster(Data);
	return Monster;
}

bool UCharacterManager::IsMonster(int id)
{
	return true;
}

void UCharacterManager::BuildNPCData(FNPCData& Data)
{
	for (int i = 0; i < Data.NPCDataList.Num(); i++)
	{
		FNPCDataOne& One = Data.NPCDataList[i];
		NPCDataList[One.ZoneX][One.ZoneY].Add(NPCData(One.PosX, One.PosY, One.PosZ, One.NPCIndex));
	}
}

FNPCData UCharacterManager::GetNPCData()
{
	FNPCData List;
	for (int i = 0; i < kMapSizeXY; i++)
	{
		for (int j = 0; j < kMapSizeXY; j++)
		{
			for (int k = 0; k < NPCDataList[i][j].Num(); k++)
			{
				FNPCDataOne One;
				NPCData& Data = NPCDataList[i][j][k];
				One.ZoneX = i;
				One.ZoneY = j;
				One.PosX = Data.PosX;
				One.PosY = Data.PosY;
				One.PosZ = Data.PosZ;
				One.NPCIndex = Data.Index;
				List.NPCDataList.Add(One);
			}
		}
	}
	return List;
}

void UCharacterManager::Clear()
{
	Inventory->Clear();

	for (int i = 0; i < kMapSizeXY; i++)
	{
		for (int j = 0; j < kMapSizeXY; j++)
		{
			NPCList[i][j].Empty();
			NPCDataList[i][j].Empty();
		}
	}
}