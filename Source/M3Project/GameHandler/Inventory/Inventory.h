#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LogicObject/Item/ItemManager.h"
#include "Resource/SaveData/SaveGameData.h"
#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct FConsumptionItemSlot
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() UConsumptionItem* Item;
	UPROPERTY() int32 Count;
};

USTRUCT(BlueprintType)
struct FResourceItemSlot
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() UResourceItem* Item;
	UPROPERTY() int32 Count;
};

USTRUCT(BlueprintType)
struct FInstallationItemSlot
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() UInstallationItem* Item;
	UPROPERTY() int32 Count;
};

UCLASS()
class M3PROJECT_API UInventory : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY() TArray<UWeaponItem*> WeaponItemList;
	UPROPERTY() TArray<UEquipmentItem*> EquipmentItemList;
	UPROPERTY() TArray<FConsumptionItemSlot> ConsumptionItemList;
	UPROPERTY() TArray<FResourceItemSlot> ResourceItemList;
	UPROPERTY() TArray<FInstallationItemSlot> InstallationItemList;
public:
	void AddItem(UItemBase* NewItem, int ItemCount = 1);
	void RemoveItem(EItemType Type, int ItemIndex, int ItemCount = 1);
	bool UseItem(EItemType Type, int ItemIndex);
	void ReleaseWeapon();
	void ReleaseEquipment(EEquipmentsType Type);
	FInventoryData GetBuildInventoryData();
	void SetBuildInventoryData(FInventoryData& Data);
	void Clear();
private:
	void Checker(EItemType Type, int ItemIndex, int ItemCount);
};