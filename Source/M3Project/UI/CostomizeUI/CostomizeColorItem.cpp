#include "CostomizeColorItem.h"
#include "Components/UniformGridSlot.h"
#include "CostomizeWidget.h"

void UCostomizeColorItem::SetColor(FColor SetUpColor)
{
	Color = SetUpColor;
	Border->SetBrushColor(FLinearColor(SetUpColor));
}

void UCostomizeColorPage::AddColorItem(FColor Color)
{
	UCostomizeColorItem* CostomizeColorItem = CreateWidget<UCostomizeColorItem>(this, CostomizeColorItemClass);
	UniformGridPanel->AddChild(CostomizeColorItem);
	UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(CostomizeColorItem->Slot);
	if (GridSlot)
	{
		int NewIndex = ColorItemList.Num();
		GridSlot->SetRow(NewIndex / kCostomizeItemRowCount);
		GridSlot->SetColumn(NewIndex % kCostomizeItemRowCount);
		CostomizeColorItem->Parent = this;
		CostomizeColorItem->Index = NewIndex;
		CostomizeColorItem->SetColor(Color);
		ColorItemList.Add(CostomizeColorItem);
	}
}

void UCostomizeColorPage::SetFocus(int Index)
{
	if (ColorItemList.Num() <= Index || Index < 0) return;
	FouceImage->RemoveFromParent();
	UniformGridPanel->AddChild(FouceImage);
	UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(ColorItemList[Index]->Slot);
	UUniformGridSlot* FouceSlot = Cast<UUniformGridSlot>(FouceImage->Slot);
	if (GridSlot && FouceSlot)
	{
		FouceSlot->SetRow(GridSlot->Row);
		FouceSlot->SetColumn(GridSlot->Column);
	}
}