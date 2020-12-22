#include "Inventory.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "GameHandler/QuestSystem/QuestSystem.h"

void UInventory::AddItem(UItemBase* NewItem, int ItemCount)
{
	switch (NewItem->GetType())
	{
	case EItemType::RESOURCE:
	{
		UResourceItem* ResourceItem = Cast<UResourceItem>(NewItem);
		if (ResourceItem)
		{
			for (int i = 0; i < ResourceItemList.Num(); i++)
			{
				if (ResourceItemList[i].Item->DefaultInfo.ID == ResourceItem->DefaultInfo.ID)
				{
					ResourceItemList[i].Count += ItemCount;
					UM3GameInstance::GetQuestSystem()->ModifyItemCount(EItemType::RESOURCE, ResourceItem->DefaultInfo.ID, ResourceItemList[i].Count);
					return;
				}
			}
			FResourceItemSlot NewItemSlot;
			NewItemSlot.Item = ResourceItem;
			NewItemSlot.Count = ItemCount;
			ResourceItemList.Add(NewItemSlot);
			UM3GameInstance::GetQuestSystem()->ModifyItemCount(EItemType::RESOURCE, ResourceItem->DefaultInfo.ID, ItemCount);
			return;
		}
	}
	break;
	case EItemType::CONSUMPTION:
	{
		UConsumptionItem* ConsumptionItem = Cast<UConsumptionItem>(NewItem);
		if (ConsumptionItem)
		{
			for (int i = 0; i < ConsumptionItemList.Num(); i++)
			{
				if (ConsumptionItemList[i].Item->DefaultInfo.ID == ConsumptionItem->DefaultInfo.ID)
				{
					ConsumptionItemList[i].Count += ItemCount;
					UM3GameInstance::GetQuestSystem()->ModifyItemCount(EItemType::CONSUMPTION, ConsumptionItem->DefaultInfo.ID, ConsumptionItemList[i].Count);
					return;
				}
			}
			FConsumptionItemSlot NewItemSlot;
			NewItemSlot.Item = ConsumptionItem;
			NewItemSlot.Count = ItemCount;
			ConsumptionItemList.Add(NewItemSlot);
			UM3GameInstance::GetQuestSystem()->ModifyItemCount(EItemType::CONSUMPTION, ConsumptionItem->DefaultInfo.ID, ItemCount);
			return;
		}
	}
	break;
	case EItemType::EQUIPMENT:
	{
		UEquipmentItem* EquipmentItem = Cast<UEquipmentItem>(NewItem);
		if (EquipmentItem)
		{
			EquipmentItemList.Add(EquipmentItem);
			return;
		}
	}
	break;
	case EItemType::WEAPON:
	{
		UWeaponItem* WeaponItem = Cast<UWeaponItem>(NewItem);
		if (WeaponItem)
		{
			WeaponItemList.Add(WeaponItem);
			return;
		}
	}
	case EItemType::INSTALLATION:
	{
		UInstallationItem* InstallationItem = Cast<UInstallationItem>(NewItem);
		if (InstallationItem)
		{
			for (int i = 0; i < InstallationItemList.Num(); i++)
			{
				if (InstallationItemList[i].Item->DefaultInfo.ID == InstallationItem->DefaultInfo.ID)
				{
					InstallationItemList[i].Count += ItemCount;
					UM3GameInstance::GetQuestSystem()->ModifyItemCount(EItemType::INSTALLATION, InstallationItem->DefaultInfo.ID, InstallationItemList[i].Count);
					return;
				}
			}
			FInstallationItemSlot NewItemSlot;
			NewItemSlot.Item = InstallationItem;
			NewItemSlot.Count = ItemCount;
			InstallationItemList.Add(NewItemSlot);
			UM3GameInstance::GetQuestSystem()->ModifyItemCount(EItemType::INSTALLATION, InstallationItem->DefaultInfo.ID, ItemCount);
			return;
		}
	}
	break;
	default:
		break;
	}
}

void UInventory::RemoveItem(EItemType Type, int ItemIndex, int ItemCount)
{
	switch (Type)
	{
	case EItemType::RESOURCE:
	{
		if (ItemIndex < ResourceItemList.Num())
		{
			ResourceItemList[ItemIndex].Count -= ItemCount;
			if (ResourceItemList[ItemIndex].Count == 0)
			{
				for (int i = ItemIndex; i < ResourceItemList.Num() - 1; i++)
				{
					ResourceItemList[i] = ResourceItemList[i + 1];
				}
				ResourceItemList.RemoveAt(ResourceItemList.Num() - 1);
			}
			UM3GameInstance::GetQuestSystem()->ModifyItemCount(Type, ItemIndex, ResourceItemList[ItemIndex].Count);
			return;
		}
	}
	break;
	case EItemType::CONSUMPTION:
	{
		if (ItemIndex < ConsumptionItemList.Num())
		{
			ConsumptionItemList[ItemIndex].Count -= ItemCount;
			if (ConsumptionItemList[ItemIndex].Count == 0)
			{
				for (int i = ItemIndex; i < ConsumptionItemList.Num() - 1; i++)
				{
					ConsumptionItemList[i] = ConsumptionItemList[i + 1];
				}
				ConsumptionItemList.RemoveAt(ConsumptionItemList.Num() - 1);
			}
			UM3GameInstance::GetQuestSystem()->ModifyItemCount(Type, ItemIndex, ConsumptionItemList[ItemIndex].Count);
			return;
		}
	}
	break;
	case EItemType::EQUIPMENT:
	{
		if (ItemIndex < EquipmentItemList.Num())
		{
			for (int i = ItemIndex; i < EquipmentItemList.Num() - 1; i++)
			{
				EquipmentItemList[i] = EquipmentItemList[i + 1];
			}
			EquipmentItemList.RemoveAt(EquipmentItemList.Num() - 1);
			return;
		}
	}
	break;
	case EItemType::WEAPON:
	{
		if (ItemIndex < WeaponItemList.Num())
		{
			for (int i = ItemIndex; i < WeaponItemList.Num() - 1; i++)
			{
				WeaponItemList[i] = WeaponItemList[i + 1];
			}
			WeaponItemList.RemoveAt(WeaponItemList.Num() - 1);
			return;
		}
	}
	break;
	case EItemType::INSTALLATION:
	{
		if (ItemIndex < InstallationItemList.Num())
		{
			InstallationItemList[ItemIndex].Count -= ItemCount;
			if (InstallationItemList[ItemIndex].Count == 0)
			{
				for (int i = ItemIndex; i < InstallationItemList.Num() - 1; i++)
				{
					InstallationItemList[i] = InstallationItemList[i + 1];
				}
				InstallationItemList.RemoveAt(InstallationItemList.Num() - 1);
			}
			UM3GameInstance::GetQuestSystem()->ModifyItemCount(Type, ItemIndex, InstallationItemList[ItemIndex].Count);
			return;
		}
	}
	break;
	}
}

bool UInventory::UseItem(EItemType Type, int ItemIndex)
{
	bool Result = false;
	APlayerCharacter* PC = UM3GameInstance::GetPC();
	switch (Type)
	{
	case EItemType::RESOURCE:
	{
		if (ResourceItemList[ItemIndex].Item->Use())
		{
			RemoveItem(Type, ItemIndex);
			Result = true;
		}
	}
	break;
	case EItemType::CONSUMPTION:
	{
		if (ConsumptionItemList[ItemIndex].Item->Use())
		{
			RemoveItem(Type, ItemIndex);
			Result = true;
		}
	}
	break;
	case EItemType::EQUIPMENT:
	{
		UEquipmentItem* OldItem = PC->ChangeEquipmentItem(EquipmentItemList[ItemIndex], (EEquipmentsType)EquipmentItemList[ItemIndex]->DefaultInfo.Type);
		Result = true;
		if (OldItem)
		{
			EquipmentItemList[ItemIndex] = OldItem;
		}
		else
		{
			RemoveItem(Type, ItemIndex);
		}
	}
	break;
	case EItemType::WEAPON:
	{
		UWeaponItem* OldItem = PC->ChangeWeaponItem(WeaponItemList[ItemIndex]);
		Result = true;
		if (OldItem)
		{
			WeaponItemList[ItemIndex] = OldItem;
		}
		else
		{
			RemoveItem(Type, ItemIndex);
		}
	}
	break;
	case EItemType::INSTALLATION:
	{
		if (InstallationItemList[ItemIndex].Item->Use())
		{
			RemoveItem(Type, ItemIndex);
			Result = true;
		}
	}
	break;
	}
	return Result;
}

void UInventory::ReleaseWeapon()
{
	APlayerCharacter* PC = UM3GameInstance::GetPC();
	UWeaponItem* OldItem = PC->ChangeWeaponItem(nullptr);
	if (OldItem) AddItem(OldItem);
}

void UInventory::ReleaseEquipment(EEquipmentsType Type)
{
	APlayerCharacter* PC = UM3GameInstance::GetPC();
	UEquipmentItem* OldItem = PC->ChangeEquipmentItem(nullptr, Type);
	if (OldItem) AddItem(OldItem);
}

FInventoryData UInventory::GetBuildInventoryData()
{
	FInventoryData InventoryData;
	for (int i = 0; i < WeaponItemList.Num(); i++)
	{
		InventoryData.WeaponItemList.Add(WeaponItemList[i]->DefaultInfo.ID);
	}
	for (int i = 0; i < EquipmentItemList.Num(); i++)
	{
		InventoryData.EquipmentItemList.Add(EquipmentItemList[i]->DefaultInfo.ID);
	}
	for (int i = 0; i < ConsumptionItemList.Num(); i++)
	{
		InventoryData.ConsumptionItemList.Add(FInventorySlotData(ConsumptionItemList[i].Item->DefaultInfo.ID, ConsumptionItemList[i].Count));
	}
	for (int i = 0; i < ResourceItemList.Num(); i++)
	{
		InventoryData.ResourceItemList.Add(FInventorySlotData(ResourceItemList[i].Item->DefaultInfo.ID, ResourceItemList[i].Count));
	}
	for (int i = 0; i < InstallationItemList.Num(); i++)
	{
		InventoryData.InstallationItemList.Add(FInventorySlotData(InstallationItemList[i].Item->DefaultInfo.ID, InstallationItemList[i].Count));
	}
	return InventoryData;
}

void UInventory::SetBuildInventoryData(FInventoryData& Data)
{
	for (int i = 0; i < Data.WeaponItemList.Num(); i++)
	{
		AddItem(UM3GameInstance::GetItemManager()->GetWeaponItem(Data.WeaponItemList[i]));
	}
	for (int i = 0; i < Data.EquipmentItemList.Num(); i++)
	{
		AddItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(Data.EquipmentItemList[i]));
	}
	for (int i = 0; i < Data.ConsumptionItemList.Num(); i++)
	{
		AddItem(UM3GameInstance::GetItemManager()->GetConsumptionItem(Data.ConsumptionItemList[i].ItemID), Data.ConsumptionItemList[i].Count);
	}
	for (int i = 0; i < Data.ResourceItemList.Num(); i++)
	{
		AddItem(UM3GameInstance::GetItemManager()->GetResourceItem(Data.ResourceItemList[i].ItemID), Data.ResourceItemList[i].Count);
	}
	for (int i = 0; i < Data.InstallationItemList.Num(); i++)
	{
		AddItem(UM3GameInstance::GetItemManager()->GetInstallationItem(Data.InstallationItemList[i].ItemID), Data.InstallationItemList[i].Count);
	}
}

void UInventory::Clear()
{
	WeaponItemList.Empty();
	EquipmentItemList.Empty();
	ConsumptionItemList.Empty();
	ResourceItemList.Empty();
	InstallationItemList.Empty();
}