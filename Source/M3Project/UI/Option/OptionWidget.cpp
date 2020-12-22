#include "OptionWidget.h"
#include "Base/M3GameInstance.h"
#include "Resource/SaveData/SaveManager.h"
#include "Kismet/GameplayStatics.h"

void UOptionWidget::SaveGame()
{
	UM3GameInstance::GetSaveManager()->SaveData();
}

void UOptionWidget::ReturnTitle()
{
	UM3GameInstance::GetSaveManager()->UnLoadData();
	UM3GameInstance::GetInstance()->bIsPlaying = false;
	UGameplayStatics::OpenLevel(this, FName("TitleLevel"));
}