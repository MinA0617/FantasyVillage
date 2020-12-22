#include "StateBarUI.h"
#include "Base/M3GameInstance.h"

void UStateBarUI::SetMaxHP(int NewMaxHP)
{
	MaxHP = NewMaxHP;
	MaxHPText->SetText(FText::FromString(FString::FromInt(MaxHP)));
}

void UStateBarUI::Update()
{
    if (UM3GameInstance::GetPC() == nullptr) return;
    const int MaxBarSize = HealthBox_Out->WidthOverride;
    const int CurrentHP = UM3GameInstance::GetPC()->GetPlayerInfo().CurrentHP;
    HealthBox_In->SetWidthOverride((MaxBarSize * CurrentHP) / MaxHP);
    CurrentHPText->SetText(FText::FromString(FString::FromInt(CurrentHP)));
}
