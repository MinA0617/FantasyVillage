#include "InvenCharacterStateWidget.h"
#include "Resource/M3ResourceManager.h"
#include "Base/M3GameInstance.h"
#include "Engine/Texture2D.h"

void UInvenCharacterStateWidget::ParentSet()
{
	SlotWeapon->ItemType = EItemType::WEAPON;
	SlotTop->ItemType = EItemType::EQUIPMENT;
	SlotBottom->ItemType = EItemType::EQUIPMENT;
	SlotHands->ItemType = EItemType::EQUIPMENT;
	SlotFeet->ItemType = EItemType::EQUIPMENT;
	SlotCap->ItemType = EItemType::EQUIPMENT;

	SlotTop->SlotIndex = (int)EEquipmentsType::TOP;
	SlotBottom->SlotIndex = (int)EEquipmentsType::BOTTOM;
	SlotHands->SlotIndex = (int)EEquipmentsType::HANDS;
	SlotFeet->SlotIndex = (int)EEquipmentsType::FEET;
	SlotCap->SlotIndex = (int)EEquipmentsType::CAP;

	SlotWeapon->GrandParentWidget = ParentWidget;
	SlotTop->GrandParentWidget = ParentWidget;
	SlotBottom->GrandParentWidget = ParentWidget;
	SlotHands->GrandParentWidget = ParentWidget;
	SlotFeet->GrandParentWidget = ParentWidget;
	SlotCap->GrandParentWidget = ParentWidget;
}

void UInvenCharacterStateWidget::SetWeapon(UWeaponItem* WeaponItem)
{
	if (WeaponItem == nullptr)
	{
		SlotWeapon->IconID = 0;
		SlotWeapon->Icon = nullptr;
		SlotWeapon->Rebuild();
	}
	else
	{
		SlotWeapon->IconID = WeaponItem->DefaultInfo.IconResource;
		UM3GameInstance::GetResourceManager()->GetAsyncObjectFromID(SlotWeapon->IconID, FStreamableDelegate::CreateUObject(SlotWeapon, &UInventorySlotWidget::SetIcon));
	}
}

void UInvenCharacterStateWidget::SetEquipment(EEquipmentsType Type, UEquipmentItem* EquipmentItem)
{
	if (EquipmentItem == nullptr)
	{
		switch (Type)
		{
		case EEquipmentsType::CAP:
			SlotCap->IconID = 0;
			SlotCap->Icon = nullptr;
			SlotCap->Rebuild();
			break;
		case EEquipmentsType::TOP:
			SlotTop->IconID = 0;
			SlotTop->Icon = nullptr;
			SlotTop->Rebuild();
			break;
		case EEquipmentsType::BOTTOM:
			SlotBottom->IconID = 0;
			SlotBottom->Icon = nullptr;
			SlotBottom->Rebuild();
			break;
		case EEquipmentsType::HANDS:
			SlotHands->IconID = 0;
			SlotHands->Icon = nullptr;
			SlotHands->Rebuild();
			break;
		case EEquipmentsType::FEET:
			SlotFeet->IconID = 0;
			SlotFeet->Icon = nullptr;
			SlotFeet->Rebuild();
			break;
		default:
			break;
		}
	}
	else
	{
		switch ((EEquipmentsType)EquipmentItem->DefaultInfo.Type)
		{
		case EEquipmentsType::CAP:
			SlotCap->IconID = EquipmentItem->DefaultInfo.IconResource;
			UM3GameInstance::GetResourceManager()->GetAsyncObjectFromID(SlotCap->IconID, FStreamableDelegate::CreateUObject(SlotCap, &UInventorySlotWidget::SetIcon));
			break;
		case EEquipmentsType::TOP:
			SlotTop->IconID = EquipmentItem->DefaultInfo.IconResource;
			UM3GameInstance::GetResourceManager()->GetAsyncObjectFromID(SlotTop->IconID, FStreamableDelegate::CreateUObject(SlotTop, &UInventorySlotWidget::SetIcon));
			break;
		case EEquipmentsType::BOTTOM:
			SlotBottom->IconID = EquipmentItem->DefaultInfo.IconResource;
			UM3GameInstance::GetResourceManager()->GetAsyncObjectFromID(SlotBottom->IconID, FStreamableDelegate::CreateUObject(SlotBottom, &UInventorySlotWidget::SetIcon));
			break;
		case EEquipmentsType::HANDS:
			SlotHands->IconID = EquipmentItem->DefaultInfo.IconResource;
			UM3GameInstance::GetResourceManager()->GetAsyncObjectFromID(SlotHands->IconID, FStreamableDelegate::CreateUObject(SlotHands, &UInventorySlotWidget::SetIcon));
			break;
		case EEquipmentsType::FEET:
			SlotFeet->IconID = EquipmentItem->DefaultInfo.IconResource;
			UM3GameInstance::GetResourceManager()->GetAsyncObjectFromID(SlotFeet->IconID, FStreamableDelegate::CreateUObject(SlotFeet, &UInventorySlotWidget::SetIcon));
			break;
		default:
			break;
		}
	}
}

void UInvenCharacterStateWidget::SetPopupItem(UItemBase* ToolTipItem)
{
	if (ToolTipItem == nullptr)
	{
		SlotToolTip->Icon = nullptr;
		TextTitle->SetText(FText::FromString(""));
		TextToolTip->SetText(FText::FromString(""));
		SlotToolTip->Rebuild();
		return;
	}
	switch (ToolTipItem->GetType())
	{
	case EItemType::RESOURCE:
	{
		UResourceItem* Item = Cast<UResourceItem>(ToolTipItem);
		if (Item)
		{
			SlotToolTip->IconID = Item->DefaultInfo.IconResource;
			TextTitle->SetText(FText::FromString(Item->DefaultInfo.Name));
			TextToolTip->SetText(FText::FromString(Item->DefaultInfo.ToolTip));
		}
		break;
	}
	case EItemType::CONSUMPTION:
	{
		UConsumptionItem* Item = Cast<UConsumptionItem>(ToolTipItem);
		if (Item)
		{
			SlotToolTip->IconID = Item->DefaultInfo.IconResource;
			TextTitle->SetText(FText::FromString(Item->DefaultInfo.Name));
			TextToolTip->SetText(FText::FromString(Item->DefaultInfo.ToolTip));
		}
	}
	break;
	case EItemType::EQUIPMENT:
	{
		UEquipmentItem* Item = Cast<UEquipmentItem>(ToolTipItem);
		if (Item)
		{
			SlotToolTip->IconID = Item->DefaultInfo.IconResource;
			TextTitle->SetText(FText::FromString(Item->DefaultInfo.Name));
			TextToolTip->SetText(FText::FromString(Item->DefaultInfo.ToolTip));
		}
	}
	break;
	case EItemType::WEAPON:
	{
		UWeaponItem* Item = Cast<UWeaponItem>(ToolTipItem);
		if (Item)
		{
			SlotToolTip->IconID = Item->DefaultInfo.IconResource;
			TextTitle->SetText(FText::FromString(Item->DefaultInfo.Name));
			TextToolTip->SetText(FText::FromString(Item->DefaultInfo.ToolTip));
		}
	}
	break;
	case EItemType::INSTALLATION:
	{
		UInstallationItem* Item = Cast<UInstallationItem>(ToolTipItem);
		if (Item)
		{
			SlotToolTip->IconID = Item->DefaultInfo.IconResource;
			TextTitle->SetText(FText::FromString(Item->DefaultInfo.Name));
			TextToolTip->SetText(FText::FromString(Item->DefaultInfo.ToolTip));
		}
	}
	break;
	default:
		break;
	}
	SlotToolTip->Icon = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture2D>(SlotToolTip->IconID);
	SlotToolTip->Rebuild();
}

