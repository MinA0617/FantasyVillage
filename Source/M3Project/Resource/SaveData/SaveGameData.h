#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LogicObject/Item/EquipmentItem.h"
#include "GameHandler/QuestSystem/QuestSystem.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "SaveGameData.generated.h"

USTRUCT(BlueprintType)
struct FGameTime
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() int32 Day;
	UPROPERTY() int32 Hour;
	UPROPERTY() int32 Minute;
	UPROPERTY() int32 Second;
};

USTRUCT(BlueprintType)
struct FNPCDataOne
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() uint16 ZoneX;
	UPROPERTY() uint16 ZoneY;
	UPROPERTY() uint16 PosX;
	UPROPERTY() uint16 PosY;
	UPROPERTY() uint16 PosZ; // 몬스터의 경우 무시
	UPROPERTY() uint16 NPCIndex;
};

USTRUCT(BlueprintType)
struct FInventorySlotData
{
	GENERATED_USTRUCT_BODY()
public:
	FInventorySlotData() {};
	FInventorySlotData(uint16 id, uint16 count)
	{
		ItemID = id;
		Count = count;
	}
public:
	UPROPERTY() uint16 ItemID;
	UPROPERTY() uint16 Count;
};

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() TArray<uint16> WeaponItemList;
	UPROPERTY() TArray<uint16> EquipmentItemList;
	UPROPERTY() TArray<FInventorySlotData> ConsumptionItemList;
	UPROPERTY() TArray<FInventorySlotData> ResourceItemList;
	UPROPERTY() TArray<FInventorySlotData> InstallationItemList;
};

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() uint16 WeaponItemID;
	UPROPERTY() uint16 CapItemID;
	UPROPERTY() uint16 TopItemID;
	UPROPERTY() uint16 BottomItemID;
	UPROPERTY() uint16 HandsItemID;
	UPROPERTY() uint16 FeetItemID;
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() FPlayerInfo PlayerInfo;
	UPROPERTY() FCustomizingInformation CustomizingInformation;
	UPROPERTY() FEquipmentData EquipmentData;
	UPROPERTY() FInventoryData InventoryData;
	UPROPERTY() TArray<FQuestState>	QuestSwitchList;
};



USTRUCT(BlueprintType)
struct FNPCData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()	TArray<FNPCDataOne> NPCDataList;
};

UCLASS()
class M3PROJECT_API USaveGameData : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()	FString SlotName;
	UPROPERTY()	int64 SlotIndex;
	UPROPERTY()	int64 SlotRealIndex;
public:
	UPROPERTY() FName LevelName;
	UPROPERTY()	FPlayerData PlayerData;
	UPROPERTY()	FNPCData NPCData;
	UPROPERTY()	FGameTime GameTime;
};
