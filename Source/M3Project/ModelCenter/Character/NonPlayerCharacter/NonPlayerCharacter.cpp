#include "NonPlayerCharacter.h"
#include "GameHandler/DialogueSystem/DialogueSystem.h"
#include "UI/UIMainWidget.h"
#include "Base/M3GameInstance.h"

ANonPlayerCharacter::ANonPlayerCharacter(const FObjectInitializer& ObjectInitializer) : ACostomizeCharacter(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANonPlayerCharacter::Converse()
{
	FDialogueSet Dialogue;
	if (UM3GameInstance::GetDialogueSystem()->GetNPCDialogueSet(Dialogue, (int)Info.NPCIndex))
	{
		UUIMainWidget::GetInstance()->ShowDialogueWidget(Dialogue);
	}
}
