#include "InventorySlotWidget.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/CharacterManager.h"
#include "Resource/M3ResourceManager.h"
#include "InventoryWidget.h"

void UInventorySlotWidget::UseItem()
{
	if (Icon != nullptr && ItemType != EItemType::NONE)
	{
		if (UM3GameInstance::GetCharacterManager()->Inventory->UseItem(ItemType, SlotIndex))
		{
			UInventoryWidget* InvenWidget = Cast<UInventoryWidget>(GrandParentWidget);
			if (InvenWidget) InvenWidget->ReBuild();
		}
	}
}

void UInventorySlotWidget::SetIcon()
{
	Icon = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture2D>(IconID);
	Rebuild();
}

void UInventorySlotStateWidget::UseItem()
{
	if (Icon != nullptr)
	{
		if (ItemType == EItemType::WEAPON)
		{
			UM3GameInstance::GetCharacterManager()->Inventory->ReleaseWeapon();
		}
		else if (ItemType == EItemType::EQUIPMENT)
		{
			UM3GameInstance::GetCharacterManager()->Inventory->ReleaseEquipment((EEquipmentsType)SlotIndex);
		}
		else return;
		UInventoryWidget* InvenWidget = Cast<UInventoryWidget>(GrandParentWidget);
		if (InvenWidget) InvenWidget->ReBuild();
	}
}