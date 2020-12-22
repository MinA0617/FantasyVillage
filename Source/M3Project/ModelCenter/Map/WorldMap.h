#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MapZone.h"
#include "Engine/DirectionalLight.h"
#include "ModelCenter/Light/SunLight.h"
#include "Atmosphere/AtmosphericFog.h"
#include "WorldMap.generated.h"

const int kMaxSight = 5;

UCLASS()
class M3PROJECT_API UWorldMap : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
	TMap<int, UMapZone*> ZoneList;
	ASunLight* SunLight;
	AAtmosphericFog* AtmosphericFog;
public:
	void			Save();
	void			Clear();
	void			Load(FVector Pos, bool Direct = false);
	bool			CheckCube(FVector Position);
	bool			CheckCanMove(FVector Position);
	bool			CheckZone(int32 ObjectID, FVector Position, int8 Rotation);
	bool			AddCubeObject(int32 ObjectID, FVector Position, int8 Rotation);
	void			RemoveCubeObject(FVector Position);
	void			DemageCube(FVector Position, int Damege);
	void			SpawnSunLight();
	bool			GetEmptyPos(FVector& Pos, int ZonePosX, int ZonePosY, int PosX, int PosY, int PosZOrFalling);
	ASunLight*		GetSunLight();
private:
	UMapZone*		GetZone(FVector Position);
	int64_3			ConvertZonePos(FVector Position, UMapZone* Zone);
	FVector			ConvertRealPos(int64_3 Position, UMapZone* Zone);
	void			AddCube(FVector Position, int8 ID, int8 Rotation);
	void			RemoveCube(FVector Position);
};
