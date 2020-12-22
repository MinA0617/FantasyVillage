#include "MapManager.h"
#include "ConstructorHelpers.h"
#include "Base/M3GameInstance.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "Engine/Classes/Materials/MaterialInstance.h"
#include "Resource/M3ResourceManager.h"
#include "GameHandler/M3GameMode.h"

UMapManager::UMapManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FString CubeDataPath = TEXT("DataTable'/Game/Resource/MapData/CubeTable.CubeTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CUBE(*CubeDataPath);
	if (DT_CUBE.Succeeded()) CubeDataTable = DT_CUBE.Object;
	PlayerPosition = FVector(0, 0, 0);
	WorldMap = ObjectInitializer.CreateDefaultSubobject<UWorldMap>(this, "WorldMap");
	MapCreator = ObjectInitializer.CreateDefaultSubobject<UMapCreator>(this, "MapCreator");
	bIsStart = false;
}

void UMapManager::Save()
{
	if (bIsStart == false) return;
	WorldMap->Save();
}

void UMapManager::Start(FVector InitPos)
{
	if (CurrentLevelName.ToString() == "DefualtLevel")
	{
		bIsStart = true;
		InitPos.Z = 0;
		PlayerPosition = InitPos;
		WorldMap->Load(InitPos, true);
	}
} 

void UMapManager::Update(FVector Pos)
{
	if (bIsStart == false) return;
	Pos.Z = 0;
	float Distance = FVector::Distance(PlayerPosition, Pos);
	if (Distance > kReloadDistance)
	{
		PlayerPosition = Pos;
		WorldMap->Load(Pos);
	}
}

void UMapManager::Clear()
{
	CurrentLevelName = FName();
	InstancedActorList.Empty();
	WorldMap->Clear();
	bIsStart = false;
}

bool UMapManager::CreateCube(int ID, FVector Pos, int Rotation)
{
	return WorldMap->AddCubeObject(ID, Pos, Rotation);
}

void UMapManager::DestroyCube(FVector Pos)
{
	WorldMap->RemoveCubeObject(Pos);
}

void UMapManager::DemageCube(FVector Pos, int Damege)
{
	WorldMap->DemageCube(Pos, Damege);
}

bool UMapManager::CheckCube(FVector Position)
{
	return WorldMap->CheckCube(Position);
}

bool UMapManager::CheckCanMove(FVector Position)
{
	return WorldMap->CheckCanMove(Position);
}

bool UMapManager::CheckObjcet(FVector Position, int ID, int Rotaiton)
{
	TArray<int64_3>& DependencyList = GetInstanceActor(ID)->DependencyList[Rotaiton];
	if (CheckCube(Position) == false) return false;
	for (int i = 0; i < DependencyList.Num(); i++)
	{
		if (CheckCube(Position + FVector(DependencyList[i].X * kCubeSizeXY, DependencyList[i].Y * kCubeSizeXY, DependencyList[i].Z * kCubeSizeZ)) == false)
		{
			return false;
		}
	}
	return true;
}

AInstancedActor* UMapManager::GetInstanceActor(int ID)
{
	if (InstancedActorList.Find(ID) == nullptr)
	{
		LoadInstanceActor(ID);
		return InstancedActorList[ID];
	}
	else
	{
		return InstancedActorList[ID];
	}
}

void UMapManager::LoadInstanceActor(int ID)
{
	AInstancedActor* InstancedActor = UM3GameInstance::GetInstance()->GetWorld()->SpawnActor<AInstancedActor>(FVector(0, 0, 0), FRotator::ZeroRotator);
	FCubeTableResource* CubeTableRow = CubeDataTable->FindRow<FCubeTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
	if (CubeTableRow == nullptr)
	{
		return;
	}
	UStaticMesh* Mesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(CubeTableRow->ResourceID);

	InstancedActor->InstancedMesh->SetStaticMesh(Mesh);
	InstancedActor->Type = CubeTableRow->Type;
	InstancedActor->Durability = CubeTableRow->Durability;

	TArray<FString> StringArray;
	CubeTableRow->Dependency.ParseIntoArray(StringArray, TEXT("/"));
	for (int i = 0; i < StringArray.Num(); i++)
	{
		TArray<FString> IntArray;
		StringArray[i].ParseIntoArray(IntArray, TEXT(","));
		int64_3 DePos = int64_3(FCString::Atoi(*IntArray[0]), FCString::Atoi(*IntArray[1]), FCString::Atoi(*IntArray[2]));
		InstancedActor->DependencyList[0].Add(DePos);
		InstancedActor->DependencyList[1].Add(int64_3(-DePos.Y, DePos.X, DePos.Z));
		InstancedActor->DependencyList[2].Add(int64_3(-DePos.X, -DePos.Y, DePos.Z));
		InstancedActor->DependencyList[3].Add(int64_3(DePos.Y, -DePos.X, DePos.Z));
	}
	InstancedActorList.Add(ID, InstancedActor);
}

bool UMapManager::GetEmptyPos(FVector& Pos, int ZonePosX, int ZonePosY, int PosX, int PosY, int PosZOrFalling)
{
	return WorldMap->GetEmptyPos(Pos, ZonePosX, ZonePosY, PosX, PosY, PosZOrFalling);
}