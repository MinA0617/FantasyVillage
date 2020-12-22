#pragma once

#include "M3Project.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Resource/SaveData/SaveZoneData.h"
#include "ModelCenter/Object/InstancedActor.h"
#include "ModelCenter/Object/BoundingBox.h"
#include "MapZone.generated.h"

const FVector kOffsetPosition = FVector(kCubeSizeXY * kZoneSize * 0.5f, kCubeSizeXY * kZoneSize * 0.5f, kCubeSizeZ * kZoneSize * 0.5f) - FVector(kCubeSizeXY * 0.5f, kCubeSizeXY * 0.5f, kCubeSizeZ * 0.5f);

enum ECubeEnum
{
	EMPTY = 0,
	LEAF,
	_UNDER_NON_CUBE_ = 100
};

struct FInstanceCubeData
{
public:
	int8	CubeID;
	int8	Rotation;
	int8	StackedDamege;
	bool	IsRender;
};

UCLASS()
class M3PROJECT_API UMapZone : public UObject
{
	GENERATED_BODY()
private:
	FInstanceCubeData						CubeList[kZoneSize][kZoneSize][kZoneSize];
	FVector									ZonePosition;
	bool									IsCreate;
	bool									IsOpend;
	UPROPERTY()	ABoundingBox*				BoundingBox;
	UPROPERTY()	TMap<int, AInstancedActor*> InstancedActorList;
public:
	void				Load(FZoneData& ZoneData);
	void				Save(FZoneData& ZoneData);
	void				Open(bool Direct = false);
	void				Create(bool Direct = false);
	void				Close();
	bool				GetIsOpend() { return IsOpend; };
	void				SetIsOpend(bool Opend) { IsOpend = Opend; };
	void				SetZonePosition(FVector ZonePos) { ZonePosition = ZonePos; };
	FVector				GetZonePosition() { return ZonePosition; };
	FInstanceCubeData&	GetData(int64_3 Position);
	bool				CheckCubeEmpty(int64_3 Position);
	bool				CheckCubeCanMove(int64_3 Position);
	void				AddCubeInstance(int64_3 Position, int32 ID, int8 Rotation);
	void				RemoveCubeIsntacne(int64_3 Position);
	void				DamegeCubeIsntacne(int64_3 Position, int Damege);
private:
	FVector				GetCubePosition(int PosX, int PosY, int PosZ);
	bool				CheckNeighborCube(int64_3 Position);
	void				DrawOne(FInstanceCubeData& CubeData, FVector Pos);
	AInstancedActor*	GetInstanceActor(int ID);
};
