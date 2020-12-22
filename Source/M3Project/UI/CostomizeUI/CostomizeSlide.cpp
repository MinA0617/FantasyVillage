#include "CostomizeSlide.h"
#include "CostomizeWidget.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/Base/CostomizeManager.h"

void UCostomizeSlide::Set(UCostomizeWidget* parent, ECostomizeParts name, FString hanglename)
{
	Parent = parent;
	PartsName = name;
	Name = FText::FromString(hanglename);
	if(NameBox) NameBox->SetText(Name);
}

void UCostomizeSlide::ModifyValue(float value)
{
	UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Parent->Owner, PartsName, Slider->GetValue());
}