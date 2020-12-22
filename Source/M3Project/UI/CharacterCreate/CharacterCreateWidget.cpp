#include "CharacterCreateWidget.h"
#include "Base/M3GameInstance.h"
#include "Resource/SaveData/SaveManager.h"

void UCharacterCreateWidget::CreateCharacter()
{
	UM3GameInstance::GetSaveManager()->GetPlayerData().PlayerInfo.CharacterName = FName(*CharacterName);
	UM3GameInstance::GetSaveManager()->GetPlayerData().CustomizingInformation = CostomizeWidget->GetOwner()->CostomizingInformation;
	UM3GameInstance::GetSaveManager()->OpenGameLevel("PrologLevel");
}

FString UCharacterCreateWidget::SetCharacterName(FString NewCharacterName)
{
	if (NewCharacterName.Len() > kMaxCharacterName)
	{
		CharacterName.Empty();
		for (int i = 0; i < kMaxCharacterName; i++)
		{
			CharacterName += NewCharacterName[i];
		}
	}
	else
	{
		CharacterName = NewCharacterName;
	}
	return CharacterName;
}