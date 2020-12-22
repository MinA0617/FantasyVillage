#include "ItemListWheelWidget.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/CharacterManager.h"
#include "Resource/M3ResourceManager.h"

void UItemListWheelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LEndEvent.BindUFunction(this, FName("SetListFromIndex"));
	REndEvent.BindUFunction(this, FName("SetListFromIndex"));

	WidgetTransformList.Add(Slot01->RenderTransform);
	WidgetTransformList.Add(Slot02->RenderTransform);
	WidgetTransformList.Add(Slot03->RenderTransform);
	WidgetTransformList.Add(Slot04->RenderTransform);
	WidgetTransformList.Add(Slot05->RenderTransform);
	WidgetTransformList.Add(Slot06->RenderTransform);
	WidgetTransformList.Add(Slot07->RenderTransform);
}

void UItemListWheelWidget::SetList(EItemType Type, int Index)
{
	CurrentType = Type;
	CurrentIndex = Index;
	SetListFromIndex();
}

bool UItemListWheelWidget::NextIndex()
{
	if (IsPlayAnimation == true) return false;
	CurrentIndex++;
	switch (CurrentType)
	{
	case EItemType::WEAPON:
	{
		if (CurrentIndex >= UM3GameInstance::GetCharacterManager()->Inventory->WeaponItemList.Num())
		{
			CurrentIndex = UM3GameInstance::GetCharacterManager()->Inventory->WeaponItemList.Num() - 1;
			return true;
		}
		break;
	}
	case EItemType::INSTALLATION:
	{
		if (CurrentIndex >= UM3GameInstance::GetCharacterManager()->Inventory->InstallationItemList.Num())
		{
			CurrentIndex = UM3GameInstance::GetCharacterManager()->Inventory->InstallationItemList.Num() - 1;
			return true;
		}
		break;
	}
	default:
		break;
	}
	PlayAnimation(LeftMoveAni);
	BindToAnimationFinished(LeftMoveAni, LEndEvent);
	IsPlayAnimation = true;
	return true;
}

bool UItemListWheelWidget::PrevIndex()
{
	if (IsPlayAnimation == true) return false;
	CurrentIndex--;
	if (CurrentIndex < 0)
	{
		CurrentIndex = 0;
		return true;
	}
	PlayAnimation(RightMoveAni);
	BindToAnimationFinished(RightMoveAni, REndEvent);
	IsPlayAnimation = true;
	return true;
}

void UItemListWheelWidget::SetListFromIndex()
{
	Slot01->SetRenderTransform(WidgetTransformList[0]);
	Slot02->SetRenderTransform(WidgetTransformList[1]);
	Slot03->SetRenderTransform(WidgetTransformList[2]);
	Slot04->SetRenderTransform(WidgetTransformList[3]);
	Slot05->SetRenderTransform(WidgetTransformList[4]);
	Slot06->SetRenderTransform(WidgetTransformList[5]);
	Slot07->SetRenderTransform(WidgetTransformList[6]);
	IsPlayAnimation = false;
	UM3ResourceManager* ResourceManager = UM3GameInstance::GetResourceManager();
	UInventory* Inven = UM3GameInstance::GetCharacterManager()->Inventory;
	switch (CurrentType)
	{
	case EItemType::WEAPON:
	{
		Slot04->IconID = Inven->WeaponItemList[CurrentIndex]->DefaultInfo.IconResource;
		ResourceManager->GetAsyncObjectFromID(Inven->WeaponItemList[CurrentIndex]->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot04, &UInventorySlotWidget::SetIcon));
		if (CurrentIndex + 1 < Inven->WeaponItemList.Num())
		{
			Slot05->IconID = Inven->WeaponItemList[CurrentIndex + 1]->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->WeaponItemList[CurrentIndex + 1]->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot05, &UInventorySlotWidget::SetIcon));
			Slot05->SetVisibility(ESlateVisibility::Visible);
			Slot05->bShowCount = false;
		}
		else Slot05->SetVisibility(ESlateVisibility::Hidden);
		if (CurrentIndex + 2 < Inven->WeaponItemList.Num())
		{
			Slot06->IconID = Inven->WeaponItemList[CurrentIndex + 2]->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->WeaponItemList[CurrentIndex + 2]->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot06, &UInventorySlotWidget::SetIcon));
			Slot06->SetVisibility(ESlateVisibility::Visible);
			Slot06->bShowCount = false;
		}
		else Slot06->SetVisibility(ESlateVisibility::Hidden);
		if (CurrentIndex + 3 < Inven->WeaponItemList.Num())
		{
			Slot07->IconID = Inven->WeaponItemList[CurrentIndex + 3]->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->WeaponItemList[CurrentIndex + 3]->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot07, &UInventorySlotWidget::SetIcon));
			Slot07->SetVisibility(ESlateVisibility::Visible);
			Slot07->bShowCount = false;
		}
		else Slot07->SetVisibility(ESlateVisibility::Hidden);
		if (CurrentIndex - 1 >= 0)
		{
			Slot03->IconID = Inven->WeaponItemList[CurrentIndex - 1]->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->WeaponItemList[CurrentIndex - 1]->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot03, &UInventorySlotWidget::SetIcon));
			Slot03->SetVisibility(ESlateVisibility::Visible);
			Slot03->bShowCount = false;
		}
		else Slot03->SetVisibility(ESlateVisibility::Hidden);
		if (CurrentIndex - 2 >= 0)
		{
			Slot02->IconID = Inven->WeaponItemList[CurrentIndex - 2]->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->WeaponItemList[CurrentIndex - 2]->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot02, &UInventorySlotWidget::SetIcon));
			Slot02->SetVisibility(ESlateVisibility::Visible);
			Slot02->bShowCount = false;
		}
		else Slot02->SetVisibility(ESlateVisibility::Hidden);
		if (CurrentIndex - 3 >= 0)
		{
			Slot01->IconID = Inven->WeaponItemList[CurrentIndex - 3]->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->WeaponItemList[CurrentIndex - 3]->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot01, &UInventorySlotWidget::SetIcon));
			Slot01->SetVisibility(ESlateVisibility::Visible);
			Slot01->bShowCount = false;
		}
		else Slot01->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	case EItemType::INSTALLATION:
	{
		Slot04->IconID = Inven->InstallationItemList[CurrentIndex].Item->DefaultInfo.IconResource;
		ResourceManager->GetAsyncObjectFromID(Inven->InstallationItemList[CurrentIndex].Item->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot04, &UInventorySlotWidget::SetIcon));
		Slot04->ItemCount = Inven->InstallationItemList[CurrentIndex].Count;
		Slot04->bShowCount = true;
		if (CurrentIndex + 1 < Inven->InstallationItemList.Num())
		{
			Slot05->IconID = Inven->InstallationItemList[CurrentIndex + 1].Item->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->InstallationItemList[CurrentIndex + 1].Item->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot05, &UInventorySlotWidget::SetIcon));
			Slot05->SetVisibility(ESlateVisibility::Visible);
			Slot05->ItemCount = Inven->InstallationItemList[CurrentIndex + 1].Count;
			Slot05->bShowCount = true;
		}
		else Slot05->SetVisibility(ESlateVisibility::Hidden);
		if (CurrentIndex + 2 < Inven->InstallationItemList.Num())
		{
			Slot06->IconID = Inven->InstallationItemList[CurrentIndex + 2].Item->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->InstallationItemList[CurrentIndex + 2].Item->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot06, &UInventorySlotWidget::SetIcon));
			Slot06->SetVisibility(ESlateVisibility::Visible);
			Slot06->ItemCount = Inven->InstallationItemList[CurrentIndex + 2].Count;
			Slot06->bShowCount = true;
		}
		else Slot06->SetVisibility(ESlateVisibility::Hidden);
		if (CurrentIndex + 3 < Inven->InstallationItemList.Num())
		{
			Slot07->IconID = Inven->InstallationItemList[CurrentIndex + 3].Item->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->InstallationItemList[CurrentIndex + 3].Item->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot07, &UInventorySlotWidget::SetIcon));
			Slot07->SetVisibility(ESlateVisibility::Visible);
			Slot07->ItemCount = Inven->InstallationItemList[CurrentIndex + 3].Count;
			Slot07->bShowCount = true;
		}
		else Slot07->SetVisibility(ESlateVisibility::Hidden);
		if (CurrentIndex - 1 >= 0)
		{
			Slot03->IconID = Inven->InstallationItemList[CurrentIndex - 1].Item->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->InstallationItemList[CurrentIndex - 1].Item->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot03, &UInventorySlotWidget::SetIcon));
			Slot03->SetVisibility(ESlateVisibility::Visible);
			Slot03->ItemCount = Inven->InstallationItemList[CurrentIndex - 1].Count;
			Slot03->bShowCount = true;
		}
		else Slot03->SetVisibility(ESlateVisibility::Hidden);
		if (CurrentIndex - 2 >= 0)
		{
			Slot02->IconID = Inven->InstallationItemList[CurrentIndex - 2].Item->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->InstallationItemList[CurrentIndex - 2].Item->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot02, &UInventorySlotWidget::SetIcon));
			Slot02->SetVisibility(ESlateVisibility::Visible);
			Slot02->ItemCount = Inven->InstallationItemList[CurrentIndex - 2].Count;
			Slot02->bShowCount = true;
		}
		else Slot02->SetVisibility(ESlateVisibility::Hidden);
		if (CurrentIndex - 3 >= 0)
		{
			Slot01->IconID = Inven->InstallationItemList[CurrentIndex - 3].Item->DefaultInfo.IconResource;
			ResourceManager->GetAsyncObjectFromID(Inven->InstallationItemList[CurrentIndex - 3].Item->DefaultInfo.IconResource, FStreamableDelegate::CreateUObject(Slot01, &UInventorySlotWidget::SetIcon));
			Slot01->SetVisibility(ESlateVisibility::Visible);
			Slot01->ItemCount = Inven->InstallationItemList[CurrentIndex - 3].Count;
			Slot01->bShowCount = true;
		}
		else Slot01->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	}
}