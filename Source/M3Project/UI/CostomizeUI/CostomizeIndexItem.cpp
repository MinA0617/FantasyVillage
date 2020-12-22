#include "CostomizeIndexItem.h"
#include "Components/UniformGridSlot.h"
#include "CostomizeWidget.h"

void UCostomizeIndexPage::SetMember(int Index)
{
	while(Index != IndexItemList.Num())
	{
		UCostomizeIndexItem* CostomizeIndexItem = CreateWidget<UCostomizeIndexItem>(this, CostomizeIndexItemClass);
		UniformGridPanel->AddChild(CostomizeIndexItem);
		UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(CostomizeIndexItem->Slot);
		if (GridSlot)
		{
			int NewIndex = IndexItemList.Num();
			GridSlot->SetRow(NewIndex / kCostomizeItemRowCount);
			GridSlot->SetColumn(NewIndex % kCostomizeItemRowCount);
			CostomizeIndexItem->Parent = this;
			CostomizeIndexItem->Index = NewIndex;
			IndexItemList.Add(CostomizeIndexItem);
		}
	}
}

void UCostomizeIndexPage::SetFocus(int Index)
{
	if (IndexItemList.Num() <= Index || Index < 0) return;
	FouceImage->RemoveFromParent();
	UniformGridPanel->AddChild(FouceImage);
	UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(IndexItemList[Index]->Slot);
	UUniformGridSlot* FouceSlot = Cast<UUniformGridSlot>(FouceImage->Slot);
	if (GridSlot && FouceSlot)
	{
		FouceSlot->SetRow(GridSlot->Row);
		FouceSlot->SetColumn(GridSlot->Column);
	}
}