#include "InventoryPageWidget.h"
#include "Resource/M3ResourceManager.h"
#include "Base/M3GameInstance.h"

void UInventoryPageWidget::NativeConstruct()
{
}

void UInventoryPageWidget::AddItem(UItemBase* Item, int Count)
{
	if (Item == nullptr) return;
	if (SlotList.Num() == ItemCount)
	{
		if (ItemCount % kHorizonSize == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(GetWorld(), SlotClass);
				UniformGridPanel->AddChild(NewSlot);
				SlotList.Add(NewSlot);
				NewSlot->ItemType = EItemType::NONE;
				NewSlot->SlotIndex = ItemCount + i;
				UUniformGridSlot* SlotSlot = Cast<UUniformGridSlot>(NewSlot->Slot);
				SlotSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
				SlotSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
				SlotSlot->SetRow(ItemCount / kHorizonSize);
				SlotSlot->SetColumn(i);
			}
		}
	}
	UTexture2D* Icon = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture2D>(Item->GetIconID());
	SlotList[ItemCount]->ItemType = Item->GetType();
	SlotList[ItemCount]->Icon = Icon;
	SlotList[ItemCount]->ItemCount = Count;
	SlotList[ItemCount]->bShowCount = bShowCount;
	SlotList[ItemCount]->Item = Item;
	SlotList[ItemCount]->GrandParentWidget = ParentWidget;
	SlotList[ItemCount]->Rebuild();

	ItemCount++;
}

void UInventoryPageWidget::Clear()
{
	UniformGridPanel->ClearChildren();
	SlotList.Empty();
	ItemCount = 0;
	for (int i = 0; i < 20; i++)
	{
		UInventorySlotWidget* InvenSlot = CreateWidget<UInventorySlotWidget>(GetWorld(), SlotClass);
		SlotList.Add(InvenSlot);
		UniformGridPanel->AddChild(InvenSlot);
		InvenSlot->ItemType = EItemType::NONE;
		InvenSlot->SlotIndex = i;
		UUniformGridSlot* SlotSlot = Cast<UUniformGridSlot>(InvenSlot->Slot);
		SlotSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		SlotSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		SlotSlot->SetRow(i / kHorizonSize);
		SlotSlot->SetColumn(i % kHorizonSize);
	}
}