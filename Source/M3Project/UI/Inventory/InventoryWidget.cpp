#include "InventoryWidget.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/CharacterManager.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"

void UInventoryWidget::NativeConstruct()
{
	Page_Weapon->ParentWidget = this;
	Page_Equipment->ParentWidget = this;
	Page_Consumption->ParentWidget = this;
	Page_Resource->ParentWidget = this;
	Page_Installation->ParentWidget = this;
	StateWidget->ParentWidget = this;
	StateWidget->ParentSet();
}

void UInventoryWidget::UseItem(EItemType Type, int Index)
{
	UM3GameInstance::GetCharacterManager()->Inventory->UseItem(Type, Index);
}

void UInventoryWidget::ReBuild()
{
	if (UM3GameInstance::GetCharacterManager())
	{
		Page_Weapon->Clear();
		Page_Equipment->Clear();
		Page_Consumption->Clear();
		Page_Resource->Clear();
		Page_Installation->Clear();
		Page_Consumption->bShowCount = true;
		Page_Resource->bShowCount = true;
		Page_Installation->bShowCount = true;
		for (int i = 0; i < UM3GameInstance::GetCharacterManager()->Inventory->WeaponItemList.Num(); i++)
		{
			Page_Weapon->AddItem(UM3GameInstance::GetCharacterManager()->Inventory->WeaponItemList[i]);
		}
		for (int i = 0; i < UM3GameInstance::GetCharacterManager()->Inventory->EquipmentItemList.Num(); i++)
		{
			Page_Equipment->AddItem(UM3GameInstance::GetCharacterManager()->Inventory->EquipmentItemList[i]);
		}
		for (int i = 0; i < UM3GameInstance::GetCharacterManager()->Inventory->ConsumptionItemList.Num(); i++)
		{
			FConsumptionItemSlot& ItemSlot = UM3GameInstance::GetCharacterManager()->Inventory->ConsumptionItemList[i];
			Page_Consumption->AddItem(ItemSlot.Item, ItemSlot.Count);
		}
		for (int i = 0; i < UM3GameInstance::GetCharacterManager()->Inventory->ResourceItemList.Num(); i++)
		{
			FResourceItemSlot& ItemSlot = UM3GameInstance::GetCharacterManager()->Inventory->ResourceItemList[i];
			Page_Resource->AddItem(ItemSlot.Item, ItemSlot.Count);
		}
		for (int i = 0; i < UM3GameInstance::GetCharacterManager()->Inventory->InstallationItemList.Num(); i++)
		{
			FInstallationItemSlot& ItemSlot = UM3GameInstance::GetCharacterManager()->Inventory->InstallationItemList[i];
			Page_Installation->AddItem(ItemSlot.Item, ItemSlot.Count);
		}
		APlayerCharacter* PC = UM3GameInstance::GetPC();
		if (PC)
		{
			StateWidget->SetPopupItem(nullptr);
			StateWidget->SetWeapon(PC->EquipmentItem.WeaponItem);
			StateWidget->SetEquipment(EEquipmentsType::CAP, PC->EquipmentItem.CapItem);
			StateWidget->SetEquipment(EEquipmentsType::TOP, PC->EquipmentItem.TopItem);
			StateWidget->SetEquipment(EEquipmentsType::BOTTOM, PC->EquipmentItem.BottomItem);
			StateWidget->SetEquipment(EEquipmentsType::HANDS, PC->EquipmentItem.HandsItem);
			StateWidget->SetEquipment(EEquipmentsType::FEET, PC->EquipmentItem.FeetItem);
		}
	}
}