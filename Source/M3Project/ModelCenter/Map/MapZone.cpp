#include "MapZone.h"
#include "Base/M3GameInstance.h"
#include "GameHandler/M3GameMode.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "Engine/Classes/Materials/MaterialInstance.h"
#include "ModelCenter/Map/MapManager.h"
#include "Components/StaticMeshComponent.h"
#include "ModelCenter/Object/ActorManager/Factory/CommandFactory.h"
#include "ModelCenter/Object/ItemActor.h"

void UMapZone::Load(FZoneData& ZoneData)
{
	int CubeIndex = 0;
	IsCreate = false;
	IsOpend = false;
	for (int i = 0; i < kZoneSize; i++)
	{
		for (int j = 0; j < kZoneSize; j++)
		{
			for (int k = 0; k < kZoneSize; k++)
			{
				CubeList[i][j][k].CubeID = ZoneData.CubeList[CubeIndex].CubeID;
				CubeList[i][j][k].Rotation = ZoneData.CubeList[CubeIndex].Rotation;
				CubeList[i][j][k].StackedDamege = 0;
				CubeList[i][j][k].IsRender = false;
				CubeIndex++;
			}
		}
	}
}

void UMapZone::Save(FZoneData& ZoneData)
{
	int CubeIndex = 0;
	for (int i = 0; i < kZoneSize; i++)
	{
		for (int j = 0; j < kZoneSize; j++)
		{
			for (int k = 0; k < kZoneSize; k++)
			{
				ZoneData.CubeList[CubeIndex].CubeID = CubeList[i][j][k].CubeID;
				ZoneData.CubeList[CubeIndex].Rotation = CubeList[i][j][k].Rotation;
				CubeIndex++;
			}
		}
	}
}

FVector UMapZone::GetCubePosition(int PosX, int PosY, int PosZ)
{
	return FVector(kCubeSizeXY * PosX, kCubeSizeXY * PosY, kCubeSizeZ * PosZ) - kOffsetPosition + ZonePosition;
}

bool UMapZone::CheckNeighborCube(int64_3 Position)
{
	if (Position.X == 0			) return true;	
	if (Position.Y == 0			) return true;	
	if (Position.Z == 0			) return true;	
	if (Position.X == kZoneSize - 1) return true;
	if (Position.Y == kZoneSize - 1) return true;
	if (Position.Z == kZoneSize - 1) return true;
	if (Position.X > 0				&& CubeList[Position.X - 1][Position.Y][Position.Z].CubeID <= ECubeEnum::_UNDER_NON_CUBE_) return true;
	if (Position.Y > 0				&& CubeList[Position.X][Position.Y - 1][Position.Z].CubeID <= ECubeEnum::_UNDER_NON_CUBE_) return true;
	if (Position.Z > 0				&& CubeList[Position.X][Position.Y][Position.Z - 1].CubeID <= ECubeEnum::_UNDER_NON_CUBE_) return true;
	if (Position.X < kZoneSize - 1	&& CubeList[Position.X + 1][Position.Y][Position.Z].CubeID <= ECubeEnum::_UNDER_NON_CUBE_) return true;
	if (Position.Y < kZoneSize - 1	&& CubeList[Position.X][Position.Y + 1][Position.Z].CubeID <= ECubeEnum::_UNDER_NON_CUBE_) return true;
	if (Position.Z < kZoneSize - 1	&& CubeList[Position.X][Position.Y][Position.Z + 1].CubeID <= ECubeEnum::_UNDER_NON_CUBE_) return true;
	return false;
}

void UMapZone::DrawOne(FInstanceCubeData& CubeData, FVector Pos)
{
	if (CubeData.CubeID <= ECubeEnum::LEAF) return;
	if (CubeData.IsRender == true) return;

	AInstancedActor* InstanceActor = GetInstanceActor(CubeData.CubeID);
	check(InstanceActor != nullptr);
	FQuat Quat = FQuat(FRotator(0, CubeData.Rotation * HALF_PI, 0));
	CubeData.IsRender = true;
	InstanceActor->InstancedMesh->AddInstance(FTransform(Quat, Pos));
}

FInstanceCubeData& UMapZone::GetData(int64_3 Position)
{
	return CubeList[Position.X][Position.Y][Position.Z];
}

bool UMapZone::CheckCubeEmpty(int64_3 Position)
{
	return CubeList[Position.X][Position.Y][Position.Z].CubeID == ECubeEnum::EMPTY;
}

bool UMapZone::CheckCubeCanMove(int64_3 Position)
{
	int ID = CubeList[Position.X][Position.Y][Position.Z].CubeID;
	if (ID == ECubeEnum::EMPTY) return true;
	else if (ID == ECubeEnum::LEAF) return false;
	AInstancedActor* InstanceActor = GetInstanceActor(ID);
	if (InstanceActor)
	{
		if (InstanceActor->Type == 2) return true;
	}
	return false;
}

void UMapZone::AddCubeInstance(int64_3 Position, int32 ID, int8 Rotation)
{
	if (IsOpend == false) return;

	//check(CubeList[Position.X][Position.Y][Position.Z].CubeID == ECubeType::EMPTY);

	if (ID == ECubeEnum::LEAF)
	{
		CubeList[Position.X][Position.Y][Position.Z].CubeID = ECubeEnum::LEAF;
		return;
	}

	AInstancedActor* InstanceActor = GetInstanceActor(ID);
	check(InstanceActor != nullptr);

	FVector WorldPosition = GetCubePosition(Position.X, Position.Y, Position.Z);
	FQuat Quat = FQuat(FRotator(0, Rotation * HALF_PI, 0));
	CubeList[Position.X][Position.Y][Position.Z].CubeID = ID;
	CubeList[Position.X][Position.Y][Position.Z].Rotation = Rotation;
	CubeList[Position.X][Position.Y][Position.Z].StackedDamege = 0;
	CubeList[Position.X][Position.Y][Position.Z].IsRender = true;
	InstanceActor->InstancedMesh->AddInstance(FTransform(Quat, WorldPosition));

	if (ID >= ECubeEnum::_UNDER_NON_CUBE_)
	{
		if (Position.X > 0 && CheckNeighborCube(Position + int64_3(-1, 0, 0)))	DrawOne(CubeList[Position.X - 1][Position.Y][Position.Z], WorldPosition - FVector(kCubeSizeXY, 0, 0));
		if (Position.Y > 0 && CheckNeighborCube(Position + int64_3(0, -1, 0)))	DrawOne(CubeList[Position.X][Position.Y - 1][Position.Z], WorldPosition - FVector(0, kCubeSizeXY, 0));
		if (Position.Z > 0 && CheckNeighborCube(Position + int64_3(0, 0, -1)))	DrawOne(CubeList[Position.X][Position.Y][Position.Z - 1], WorldPosition - FVector(0, 0, kCubeSizeZ));
		if (Position.X < kZoneSize - 1 && CheckNeighborCube(Position + int64_3(1, 0, 0)))	DrawOne(CubeList[Position.X + 1][Position.Y][Position.Z], WorldPosition + FVector(kCubeSizeXY, 0, 0));
		if (Position.Y < kZoneSize - 1 && CheckNeighborCube(Position + int64_3(0, 1, 0)))	DrawOne(CubeList[Position.X][Position.Y + 1][Position.Z], WorldPosition + FVector(0, kCubeSizeXY, 0));
		if (Position.Z < kZoneSize - 1 && CheckNeighborCube(Position + int64_3(0, 0, 1)))	DrawOne(CubeList[Position.X][Position.Y][Position.Z + 1], WorldPosition + FVector(0, 0, kCubeSizeZ));
	}
	return;
}

void UMapZone::RemoveCubeIsntacne(int64_3 Position)
{
	if (IsOpend == false) return;

	AInstancedActor* InstanceActor = GetInstanceActor(CubeList[Position.X][Position.Y][Position.Z].CubeID);
	check(InstanceActor != nullptr);

	TArray<int> InstanceID = InstanceActor->InstancedMesh->GetInstancesOverlappingSphere(GetCubePosition(Position.X, Position.Y, Position.Z), 0.1);
	if (InstanceID.Num() == 0) return;
	for (int i = 0; i < InstanceID.Num(); i++)
	{
		FTransform Transform;
		InstanceActor->InstancedMesh->GetInstanceTransform(InstanceID[i], Transform);
		if (Transform.GetLocation().Equals(GetCubePosition(Position.X, Position.Y, Position.Z), 1.0f))
		{
			InstanceActor->InstancedMesh->RemoveInstance(InstanceID[i]);
			CubeList[Position.X][Position.Y][Position.Z].CubeID = ECubeEnum::EMPTY;
			CubeList[Position.X][Position.Y][Position.Z].Rotation = 0;
			CubeList[Position.X][Position.Y][Position.Z].StackedDamege = 0;
			CubeList[Position.X][Position.Y][Position.Z].IsRender = false;

			FVector WorldPosition = GetCubePosition(Position.X, Position.Y, Position.Z);

			if (Position.X > 0)				DrawOne(CubeList[Position.X - 1][Position.Y][Position.Z], WorldPosition - FVector(kCubeSizeXY, 0, 0));
			if (Position.Y > 0)				DrawOne(CubeList[Position.X][Position.Y - 1][Position.Z], WorldPosition - FVector(0, kCubeSizeXY, 0));
			if (Position.Z > 0)				DrawOne(CubeList[Position.X][Position.Y][Position.Z - 1], WorldPosition - FVector(0, 0, kCubeSizeZ));
			if (Position.X < kZoneSize - 1)	DrawOne(CubeList[Position.X + 1][Position.Y][Position.Z], WorldPosition + FVector(kCubeSizeXY, 0, 0));
			if (Position.Y < kZoneSize - 1)	DrawOne(CubeList[Position.X][Position.Y + 1][Position.Z], WorldPosition + FVector(0, kCubeSizeXY, 0));
			if (Position.Z < kZoneSize - 1)	DrawOne(CubeList[Position.X][Position.Y][Position.Z + 1], WorldPosition + FVector(0, 0, kCubeSizeZ));
		}
	}
	return;
}

void UMapZone::DamegeCubeIsntacne(int64_3 Position, int Damege)
{
	if (IsOpend == false) return;
	int ID = CubeList[Position.X][Position.Y][Position.Z].CubeID;
	if (ID <= LEAF) return;
	AInstancedActor* InstanceActor = GetInstanceActor(ID);
	check(InstanceActor != nullptr);

	FInstanceCubeData& Data = GetData(Position);
	Data.StackedDamege += Damege;

	if (Data.StackedDamege >= InstanceActor->Durability)
	{
		RemoveCubeIsntacne(Position);
		AItemActor* ItemActor = InstanceActor->GetWorld()->SpawnActor<AItemActor>(AItemActor::StaticClass());
		ItemActor->TeleportTo(GetCubePosition(Position.X, Position.Y, Position.Z), FRotator::ZeroRotator);
		ItemActor->BuildFromIndex(EItemType::INSTALLATION, ID);
	}
}

void UMapZone::Open(bool Direct)
{
	check(IsOpend == false);
	if (IsCreate)
	{
		for (TPair<int, AInstancedActor*> temp : InstancedActorList)
		{
			temp.Value->SetActorHiddenInGame(false);
		}
		BoundingBox->SetActorHiddenInGame(false);
	}
	else
	{
		Create(Direct);
	}
	IsOpend = true;
	return;
}

void UMapZone::Create(bool Direct)
{
	check(IsCreate == false);
	AInstancedActor* InstanceActor = nullptr;
	FQuat Rotation = FQuat();
	FVector Position;
	for (int i = 0; i < kZoneSize; i++)
	{
		for (int j = 0; j < kZoneSize; j++)
		{
			for (int k = 0; k < kZoneSize; k++)
			{
				if (CubeList[i][j][k].CubeID <= ECubeEnum::LEAF) continue;
				if (CheckNeighborCube(int64_3(i, j, k)) == false) continue;

				InstanceActor = GetInstanceActor(CubeList[i][j][k].CubeID);
				check(InstanceActor != nullptr);
				Position = GetCubePosition(i, j, k);
				Rotation = FQuat(FRotator(0, CubeList[i][j][k].Rotation * HALF_PI, 0));
				FTransform Transform(Rotation, Position);
				if (UE_EDITOR)
				{
					TArray<int> InstanceID = InstanceActor->InstancedMesh->GetInstancesOverlappingSphere(Position, 1.0f);
					if (InstanceID.Num() != 0)
					{
						FTransform Transform2 = FTransform::Identity;
						InstanceActor->InstancedMesh->GetInstanceTransform(InstanceID[0], Transform2);
						FVector Pos = Transform2.GetLocation();
						if (Pos == Position)
						{
							check(false);
						}
					}
				}
				if (Direct)
				{
					InstanceActor->InstancedMesh->AddInstance(Transform);
					CubeList[i][j][k].IsRender = true;
				}
				else
				{
					CCommandFactory::AddInstanceCommand(CubeList[i][j][k], Transform, InstanceActor->InstancedMesh);
				}
				InstanceActor = nullptr;
			}
		}
	}
	if (UE_EDITOR)
	{
		BoundingBox = AM3GameMode::GetInstance()->GetWorld()->SpawnActor<ABoundingBox>(ZonePosition, FRotator::ZeroRotator);
		BoundingBox->SetSize(int64_3(kZoneSize * kCubeSizeXY, kZoneSize * kCubeSizeXY, kZoneSize * kCubeSizeZ));
		BoundingBox->SetActorLocation(ZonePosition);
	}

	IsCreate = true;
	return;
}

void UMapZone::Close()
{
	for (TPair<int, AInstancedActor*> temp : InstancedActorList)
	{
		temp.Value->SetActorHiddenInGame(true);
	}
	if (UE_EDITOR)
	{
		if(BoundingBox) BoundingBox->SetActorHiddenInGame(true);
	}
	IsOpend = false;
	return;
}

AInstancedActor* UMapZone::GetInstanceActor(int ID)
{
	if (InstancedActorList.Find(ID) == nullptr)
	{
		AInstancedActor* NewInstanceActor = AM3GameMode::GetInstance()->GetWorld()->SpawnActor<AInstancedActor>(FVector(0, 0, 0), FRotator::ZeroRotator);
		AInstancedActor* InstanceActor = UM3GameInstance::GetMapManager()->GetInstanceActor(ID);
		NewInstanceActor->InstancedMesh->SetStaticMesh(InstanceActor->InstancedMesh->GetStaticMesh());
		NewInstanceActor->Type = InstanceActor->Type;

		NewInstanceActor->SetCollisionFromType();

		NewInstanceActor->Durability = InstanceActor->Durability;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < InstanceActor->DependencyList[i].Num(); j++)
			{
				NewInstanceActor->DependencyList[i].Add(InstanceActor->DependencyList[i][j]);
			}
		}
		InstancedActorList.Add(ID, NewInstanceActor);
		return InstancedActorList[ID];
	}
	else
	{
		return InstancedActorList[ID];
	}
}