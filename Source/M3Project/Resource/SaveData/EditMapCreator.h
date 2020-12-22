#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveManager.h"
#include "Engine/DataTable.h"
#include <vector>
#include "EditMapCreator.generated.h"

typedef std::vector<std::vector<std::vector<FCubeData>>> Vec_ZoneDataList;

UCLASS()
class M3PROJECT_API UEditMapCreator : public UObject
{
	GENERATED_BODY()
public:
	UEditMapCreator();
	static UDataTable* CubeDataTable;
	static void Create(USaveGameData* NewGameData);
	static void MonsterCreate(USaveGameData* NewGameData);
	static void PollTree(Vec_ZoneDataList& CubeData, int MaxRate, int MinRate);
	static void PollList(Vec_ZoneDataList& CubeData, int MaxRate, int MinRate);
	static void PollGrass(Vec_ZoneDataList& CubeData, int MaxRate, int MinRate);
	static void PollPoint(Vec_ZoneDataList& CubeData, int X, int Y, int Height);
	static void Save(Vec_ZoneDataList& CubeData);
};
