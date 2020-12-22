#include "ItemWidgetPage.h"
#include "WidgetTree.h"
#include "Components/UniformGridSlot.h"

UItemWidgetPage::UItemWidgetPage(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	HorizonCount = 5;
	PaddingSize = 15;
}

void UItemWidgetPage::SetUnifom()
{
	UnifomGrid->SlotPadding = FMargin(PaddingSize);
	for (int i = 0; i < UniformList.Num(); i++)
	{
		UnifomGrid->AddChild(UniformList[i]);
		UUniformGridSlot* TempSlot = Cast<UUniformGridSlot>(UniformList[i]->Slot);
		TempSlot->SetRow(i / HorizonCount);
		TempSlot->SetColumn(i % HorizonCount);
	}
}

void UItemWidgetPage::AddItem(UUserWidget* item)
{
	UniformList.Add(item);
}
