#include "WorldMap.h"
#include "Base/M3GameInstance.h"
#include "Resource/M3ResourceManager.h"
#include "Resource/SaveData/SaveManager.h"
#include "ModelCenter/Object/ActorManager/Factory/CommandFactory.h"
#include "ModelCenter/Character/CharacterManager.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "Atmosphere/AtmosphericFogComponent.h"
#include "MapManager.h"

UMapZone* UWorldMap::GetZone(FVector Position)
{
	int64 PosX = FMath::RoundToInt(Position.X / (kZoneSize * kCubeSizeXY));
	int64 PosY = FMath::RoundToInt(Position.Y / (kZoneSize * kCubeSizeXY));

	if (kMapSizeXY <= PosX || kMapSizeXY <= PosY) return nullptr;

	if (ZoneList.Find(PosX << 16 | PosY) == nullptr) return nullptr;

	return ZoneList[PosX << 16 | PosY];
}

int64_3 UWorldMap::ConvertZonePos(FVector Position, UMapZone* Zone)
{
	FVector InZonePos = Position - Zone->GetZonePosition();
	InZonePos += kOffsetPosition;

	int32 PosX = FMath::RoundToInt(InZonePos.X / (float)kCubeSizeXY);
	int32 PosY = FMath::RoundToInt(InZonePos.Y / (float)kCubeSizeXY);
	int32 PosZ = FMath::RoundToInt(InZonePos.Z / (float)kCubeSizeZ );

	PosX = FMath::Min(kZoneSize, FMath::Max(PosX, 0));
	PosY = FMath::Min(kZoneSize, FMath::Max(PosY, 0));
	PosZ = FMath::Min(kZoneSize, FMath::Max(PosZ, 0));

	return int64_3(PosX, PosY, PosZ);
}

FVector UWorldMap::ConvertRealPos(int64_3 Position, UMapZone* Zone)
{
	FVector Result = FVector();
	Result.X = Position.X * (float)kCubeSizeXY;
	Result.Y = Position.Y * (float)kCubeSizeXY;
	Result.Z = Position.Z * (float)kCubeSizeZ;
	Result += Zone->GetZonePosition();
	Result -= kOffsetPosition;
	return Result;
}

bool UWorldMap::GetEmptyPos(FVector& Pos, int ZonePosX, int ZonePosY, int PosX, int PosY, int PosZOrFalling)
{
	UMapZone* Zone = ZoneList[(ZonePosX) << 16 | (ZonePosY)];
	if (PosZOrFalling != -1)
	{
		for (int i = PosZOrFalling; i < kZoneSize; i++)
		{
			if (Zone->CheckCubeEmpty(int64_3(PosX, PosY, i)) == true)
			{
				Pos = ConvertRealPos(int64_3(PosX, PosY, i), Zone);
				return true;
			}
		}
	}
	else
	{
		for (int i = kZoneSize - 1; i >= 0; i--)
		{
			if (Zone->CheckCubeEmpty(int64_3(PosX, PosY, i)) == false)
			{
				Pos = ConvertRealPos(int64_3(PosX, PosY, i + 1), Zone);
				return true;
			}
		}
	}
	return false;
}

void UWorldMap::Save()
{
	int Index = UM3GameInstance::GetSaveManager()->GetIndex();
	for (int i = 0; i < kMapSizeXY; i++)
	{
		for (int j = 0; j < kMapSizeXY; j++)
		{
			if (ZoneList.Find(i << 16 | j))
			{
				FZoneData Data;
				ZoneList[i << 16 | j]->Save(Data);
				UM3GameInstance::GetSaveManager()->SaveZoneData(Index, Data, i, j);
			}
		}
	}
}

void UWorldMap::Clear()
{
	ZoneList.Empty();
	SunLight = nullptr;
	AtmosphericFog = nullptr;
}

void UWorldMap::Load(FVector Pos, bool Direct)
{
	int PosX = FMath::RoundToInt((Pos.X - (kZoneSize * kCubeSizeXY * 0.5f)) / (kZoneSize * kCubeSizeXY));
	int PosY = FMath::RoundToInt((Pos.Y - (kZoneSize * kCubeSizeXY * 0.5f)) / (kZoneSize * kCubeSizeXY));

	int SlotIndex = UM3GameInstance::GetSaveManager()->GetIndex();

	for (int i = -kMaxSight; i <= kMaxSight; i++)
	{
		for (int j = -kMaxSight; j <= kMaxSight; j++)
		{
			if (PosX + i >= 0 && PosY + j >= 0 && PosX + i < kMapSizeXY && PosY + j < kMapSizeXY)
			{
				if (ZoneList.Find((PosX + i) << 16 | (PosY + j)) == nullptr)
				{
					UMapZone* NewZone = NewObject<UMapZone>();
					NewZone->AddToRoot();
					ZoneList.Add((PosX + i) << 16 | (PosY + j), NewZone);
					NewZone->SetZonePosition(FVector(kZoneSize * kCubeSizeXY * (PosX + i), kZoneSize * kCubeSizeXY * (PosY + j), 0));
					if (Direct)
					{
						FZoneData ZoneData;
						UM3GameInstance::GetSaveManager()->LoadZoneData(SlotIndex, ZoneData, PosX + i, PosY + j);
						NewZone->Load(ZoneData);
						NewZone->Open(Direct);

					}
					else
					{
						CCommandFactory::OpenZoneCommand(NewZone, PosX + i, PosY + j);
						NewZone->SetIsOpend(true);
					}
				}
				else if (ZoneList[(PosX + i) << 16 | (PosY + j)]->GetIsOpend() == false)
				{
					ZoneList[(PosX + i) << 16 | (PosY + j)]->Open(Direct);
				}
				UM3GameInstance::GetCharacterManager()->LoadZoneNPC(PosX + i, PosY + j);
			}
		}
	}
	for (auto temp : ZoneList)
	{
		if (temp.Value->GetIsOpend() == false) continue;
		int PosXt = temp.Key >> 16;
		int PosYt = temp.Key - (PosXt << 16);
		if (FMath::Abs(PosXt - PosX) > kMaxSight || FMath::Abs(PosYt - PosY) > kMaxSight)
		{
			temp.Value->Close();
			UM3GameInstance::GetCharacterManager()->RemoveZoneNPC(PosXt, PosYt);
		}
	}
}

bool UWorldMap::CheckCube(FVector Position)
{
	UMapZone* Zone = GetZone(Position);
	if (Zone == nullptr) return false;
	int64_3 Pos = ConvertZonePos(Position, Zone);
	return Zone->CheckCubeEmpty(Pos);
}

bool UWorldMap::CheckCanMove(FVector Position)
{
	UMapZone* Zone = GetZone(Position);
	if (Zone == nullptr) return false;
	int64_3 Pos = ConvertZonePos(Position, Zone);
	return Zone->CheckCubeCanMove(Pos);
}

void UWorldMap::AddCube(FVector Position, int8 ID, int8 Rotation)
{
	UMapZone* Zone = GetZone(Position);
	int64_3 Pos = ConvertZonePos(Position, Zone);
	Zone->AddCubeInstance(Pos, ID, Rotation);
	return;
}

void UWorldMap::RemoveCube(FVector Position)
{
	UMapZone* Zone = GetZone(Position);
	int64_3 Pos = ConvertZonePos(Position, Zone);
	Zone->RemoveCubeIsntacne(Pos);
	return;
}

bool UWorldMap::CheckZone(int32 ObjectID, FVector Position, int8 Rotation)
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	UM3GameInstance* M3GameInstance = Cast<UM3GameInstance>(GameInstance);
	if (M3GameInstance == nullptr) return false;

	AInstancedActor* CubeInfo = M3GameInstance->MapManager->GetInstanceActor(ObjectID);

	if (CheckCube(Position) == false) return false;
	for (int i = 0; i < CubeInfo->DependencyList[Rotation].Num(); i++)
	{
		if (CheckCube(Position + FVector(CubeInfo->DependencyList[Rotation][i].X * kCubeSizeXY,
										CubeInfo->DependencyList[Rotation][i].Y * kCubeSizeXY,
										CubeInfo->DependencyList[Rotation][i].Z * kCubeSizeZ)) == false)
		{ return false; };
	}
	return true;
}

bool UWorldMap::AddCubeObject(int32 ObjectID, FVector Position, int8 Rotation)
{
	if (CheckZone(ObjectID, Position, Rotation) == false) return false;

	AInstancedActor* CubeInfo = UM3GameInstance::GetMapManager()->GetInstanceActor(ObjectID);

	AddCube(Position, ObjectID, Rotation);
	for (int i = 0; i < CubeInfo->DependencyList[Rotation].Num(); i++)
	{
		AddCube(Position + FVector(CubeInfo->DependencyList[Rotation][i].X * kCubeSizeXY,
			CubeInfo->DependencyList[Rotation][i].Y * kCubeSizeXY,
			CubeInfo->DependencyList[Rotation][i].Z * kCubeSizeZ), ECubeEnum::LEAF, Rotation);
	}
	return true;
}

void UWorldMap::RemoveCubeObject(FVector Position)
{
	UMapZone* Zone = GetZone(Position);
	int64_3 Pos = ConvertZonePos(Position, Zone);
	FInstanceCubeData& Data = Zone->GetData(Pos);

	if (Data.CubeID <= LEAF) return;
	AInstancedActor* CubeInfo = UM3GameInstance::GetMapManager()->GetInstanceActor(Data.CubeID);

	RemoveCube(Position);
	for (int i = 0; i < CubeInfo->DependencyList[Data.Rotation].Num(); i++)
	{
		RemoveCube(Position + FVector(CubeInfo->DependencyList[Data.Rotation][i].X * kCubeSizeXY,
			CubeInfo->DependencyList[Data.Rotation][i].Y * kCubeSizeXY,
			CubeInfo->DependencyList[Data.Rotation][i].Z * kCubeSizeZ));
	}
}

void UWorldMap::DemageCube(FVector Position, int Damege)
{
	UMapZone* Zone = GetZone(Position);
	int64_3 Pos = ConvertZonePos(Position, Zone);
	Zone->DamegeCubeIsntacne(Pos, Damege);
}

void UWorldMap::SpawnSunLight()
{
	SunLight = UM3GameInstance::GetPC()->GetWorld()->SpawnActor<ASunLight>();
}

ASunLight* UWorldMap::GetSunLight()
{
	return SunLight;
}