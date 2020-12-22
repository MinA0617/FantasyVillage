// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveZoneData.generated.h"

const int kMapSizeXY = 20;
const int kZoneSize = 50;
const int kCubeSizeXY = 100;
const int kCubeSizeZ = 80;

USTRUCT(BlueprintType)
struct FCubeData
{
	GENERATED_USTRUCT_BODY()
public:
	FCubeData() {};
	FCubeData(uint8 cubeid, uint8 rotation)
	{
		CubeID = cubeid;
		Rotation = rotation;
	}
public:
	uint8 CubeID;
	uint8 Rotation;
};

USTRUCT(BlueprintType)
struct FZoneData
{
	GENERATED_USTRUCT_BODY()
public:
	FZoneData()
	{
		CubeList.SetNum(kZoneSize * kZoneSize * kZoneSize);
	}
public:
	TArray<FCubeData> CubeList;
};

UCLASS()
class M3PROJECT_API USaveZoneData : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	FString SlotName;
	UPROPERTY(EditDefaultsOnly)
	int32 SlotIndex;
	UPROPERTY(EditDefaultsOnly)
	FZoneData ZoneData;
};
