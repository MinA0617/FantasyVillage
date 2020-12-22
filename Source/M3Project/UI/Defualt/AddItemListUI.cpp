#include "AddItemListUI.h"
#include "TimerManager.h"
#include "Components/VerticalBoxSlot.h"

void UAddItemListUI::AddAddItemWidget(UItemBase* Item)
{
	UAddItemUI* AddItem = CreateWidget<UAddItemUI>(GetWorld(), AddItemClass);
	AddItem->SetItemAndStart(this, Item);
	if (AddItem)
	{
		if (AddItemList.Num() > 3)
		{
			TimerOut();
			float Rate0 = GetWorld()->GetTimerManager().GetTimerRate(Timer[0]);
			float Rate1 = GetWorld()->GetTimerManager().GetTimerRate(Timer[1]);
			float Rate2 = GetWorld()->GetTimerManager().GetTimerRate(Timer[2]);
			int flag = 0;
			if (Rate0 > Rate1) flag = 1;
			if (Rate1 > Rate2 && Rate0 > Rate2) flag = 2;
			GetWorld()->GetTimerManager().ClearTimer(Timer[flag]);
		}
		AddItemList.Empty();
		TArray<UWidget*> Array = VBox->GetAllChildren();
		for(int i = 0; i < Array.Num(); i++)
		{
			VBox->RemoveChild(Array[i]);
		}
		VBox->AddChild(AddItem);
		AddItemList.Add(AddItem);
		UVerticalBoxSlot* NewSlot = Cast<UVerticalBoxSlot>(AddItem->Slot);
		if (NewSlot)
		{
			NewSlot->SetPadding(FMargin(5.0f));
		}
		for (int i = 0; i < Array.Num(); i++)
		{
			VBox->AddChild(Array[i]);
			AddItemList.Add(Cast<UAddItemUI>(Array[i]));
			UVerticalBoxSlot* BSlot = Cast<UVerticalBoxSlot>(Array[i]->Slot);
			if (BSlot)
			{
				BSlot->SetPadding(FMargin(30.0f, 5.0f, 5.0f, 5.0f));
			}
		}
		for (int i = 0; i < 3; i++)
		{
			if (GetWorld()->GetTimerManager().IsTimerActive(Timer[i]) == false)
			{
				GetWorld()->GetTimerManager().SetTimer(Timer[i], this, &UAddItemListUI::TimerOut, 3.0f);
				return;
			}
		}
	}
}

void UAddItemListUI::RemoveAddItemWidget()
{
	TArray<UWidget*> Array = VBox->GetAllChildren();
	if (Array.Num() > 0)
	{
		VBox->RemoveChildAt(Array.Num() - 1);
	}
	if (AddItemList.Num() > 0)
	{
		AddItemList.RemoveAt(AddItemList.Num() - 1);
	}
}

void UAddItemListUI::TimerOut()
{
	if (AddItemList.Num() > 0) AddItemList[AddItemList.Num() - 1]->EndAnimation();
}