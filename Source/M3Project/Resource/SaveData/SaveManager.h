// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveGameData.h"
#include "SaveZoneData.h"
#include "SaveManager.generated.h"

const int kMaxSaveSlot = 3;
const int kStartHour = 8;

USTRUCT(BlueprintType)
struct FGameSlotData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite) bool bIsNotData;
	UPROPERTY(BlueprintReadWrite) FName CharacterName;
	UPROPERTY(BlueprintReadWrite) int GameTime;
};

UCLASS()
class M3PROJECT_API USaveManager : public UObject
{
	GENERATED_BODY()
public:
	USaveManager(const FObjectInitializer& ObjectInitializer);
public:
	int					GetIndex();
	bool				NewData(int GameDataIndex);
	void				NewEditData();
	bool				LoadData(int GameDataIndex);
	bool				DeleteData(int GameDataIndex);
	bool				UnLoadData();
	bool				SaveData();
	bool				LoadZoneData(int SlotIndex, FZoneData& Output, int PosX, int PosY);
	bool				SaveZoneData(int SlotIndex, FZoneData& input, int PosX, int PosY);
	FPlayerData&		GetPlayerData();
	FNPCData&			GetNPCData();
	FGameTime&			GetGameTime();
	void				OpenGameLevel(FName LevelName);
	FGameSlotData		GetSlotData(int Index);
private:
	UPROPERTY()
	USaveGameData*		CurrentGameData;
	bool				IsLoad;
	bool				bIsEditorMode;
public:
	bool				EditorMode();
};