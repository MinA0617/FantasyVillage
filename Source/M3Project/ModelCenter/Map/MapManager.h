#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Engine/AssetManager.h"
#include "MapCreator.h"
#include "GameFramework/Actor.h"
#include "M3Project.h"
#include "ModelCenter/Object/InstancedActor.h"
#include "WorldMap.h"
#include "MapManager.generated.h"

const float		kReloadDistance = 5000.0f;

UCLASS()
class M3PROJECT_API UMapManager : public UObject
{
	GENERATED_BODY()
public:
	friend class UMapCreator;
	UMapManager(const FObjectInitializer& ObjectInitializer);
private:
	bool	bIsStart;
	FVector PlayerPosition;
private:
	UPROPERTY(EditDefaultsOnly)	UDataTable* CubeDataTable;
	UPROPERTY(EditDefaultsOnly)	UWorldMap* WorldMap;
	UPROPERTY()	TMap<int, AInstancedActor*> InstancedActorList;
public:
	UPROPERTY(EditDefaultsOnly) UMapCreator* MapCreator;
	FName				CurrentLevelName;
public:
	void				Save();
	void				Start(FVector InitPos);
	void				Update(FVector Pos);
	void				Clear();
public:
	bool				CreateCube(int ID, FVector Pos, int Rotation);
	void				DestroyCube(FVector Pos);
	void				DemageCube(FVector Pos, int Damege);
	bool				CheckCube(FVector Position);
	bool				CheckCanMove(FVector Position);
	bool				CheckObjcet(FVector Position, int ID, int Rotaiton = 0);
	AInstancedActor*	GetInstanceActor(int ID);
	bool				GetEmptyPos(FVector& Pos, int ZonePosX, int ZonePosY, int PosX, int PosY, int PosZOrFalling = -1);
	UWorldMap*			GetWorldMap() { return WorldMap; };
private:
	void				LoadInstanceActor(int ID);
};

USTRUCT(BlueprintType)
struct FCubeTableResource : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int64	ResourceID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8	Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int64	Durability; // 0일 경우 부수지 못한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString	Dependency;
};