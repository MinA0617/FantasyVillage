#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EquipmentItem.h"
#include "ConsumptionItem.h"
#include "WeaponItem.h"
#include "ResourceItem.h"
#include "InstallationItem.h"
#include "ItemManager.generated.h"

UCLASS()
class M3PROJECT_API UItemManager : public UObject
{
	GENERATED_BODY()
public:
	UItemManager();
	UDataTable* WeaponItemTable;
	UDataTable* EquipmentItemTable;
	UDataTable* ConsumptionItemTable;
	UDataTable* ResourceItemTable;
	UDataTable* InstallationItemTable;
public:
	UItemBase* GetItem(EItemType Type, int ID);
	UWeaponItem* GetWeaponItem(int ID);
	UEquipmentItem* GetEquipmentItem(int ID);
	UConsumptionItem* GetConsumptionItem(int ID);
	UResourceItem* GetResourceItem(int ID);
	UInstallationItem* GetInstallationItem(int ID);
public:
	void	AsyncItemResourceLoad(EItemType Type, int ID);
};
