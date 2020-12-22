#include "DialogueWidget.h"
#include "Base/M3GameInstance.h"
#include "GameHandler/CinematicSystem/CinematicSystem.h"
#include "GameHandler/QuestSystem/QuestSystem.h"
#include "GameHandler/DialogueSystem/DialogueSystem.h"
#include "UI/UIMainWidget.h"

void UDialogueWidget::SetDialogue(FDialogueSet& NewDialogueSet)
{
	DialogueSet = NewDialogueSet;
	SetIndex = 0;
	FocusIndex = 0;
	UDialogue_Text* Dialogue = Cast<UDialogue_Text>(DialogueSet.DialogueList[0]);
	if (Dialogue)
	{
		SetString(Dialogue->Text);
	}
}

void UDialogueWidget::FocusChoice(int Index)
{
	if (ChoiceList.Num() == 0) return;
	if (ChoiceList.Num() <= Index) return;
	for (int i = 0; i < ChoiceList.Num(); i++)
	{
		ChoiceList[i]->SetFocus(false);
	}
	ChoiceList[Index]->SetFocus(true);
	FocusIndex = Index;
}

void UDialogueWidget::FocusChoiceNext(bool bIsNext)
{
	if (ChoiceList.Num() == 0) return;
	if (bIsNext) FocusIndex++;
	else FocusIndex--;
	if (ChoiceList.Num() <= FocusIndex) FocusIndex--;
	if (0 > FocusIndex) FocusIndex = 0;
	for (int i = 0; i < ChoiceList.Num(); i++)
	{
		ChoiceList[i]->SetFocus(false);
	}
	ChoiceList[FocusIndex]->SetFocus(true);
}

bool UDialogueWidget::Next()
{
	if (ChoiceList.Num() != 0)
	{
		return true;
	}
	SetIndex++;
	if (SetIndex >= DialogueSet.DialogueList.Num())
	{
		End();
		return false;
	}
	switch (DialogueSet.DialogueList[SetIndex]->GetStyle())
	{
	case EDialogueStyle::TEXT:
	{
		UDialogue_Text* Dialogue = Cast<UDialogue_Text>(DialogueSet.DialogueList[SetIndex]);
		if (Dialogue)
		{
			NextString(Dialogue->Text);
		}
	}
	break;
	case EDialogueStyle::CHOICE_OPTION:
	{
		UDialogue_ChoiceOption* Dialogue = Cast<UDialogue_ChoiceOption>(DialogueSet.DialogueList[SetIndex]);
		if (Dialogue)
		{
			for (int i = 0; i < Dialogue->List.Num(); i++)
			{
				UDialogueChoiceWidget* Choice = CreateWidget<UDialogueChoiceWidget>(GetWorld(), ChoiceWidget);
				Choice->SetString(Dialogue->List[i].ChoiceText);
				Choice->JumpingIndex = Dialogue->List[i].JumpSection;
				Choice->ChoiceIndex = i;
				Choice->ParentWidget = this;
				ChoiceList.Add(Choice);
				VerticalBox->AddChild(Choice);
			}
		}
	}
	break;
	case EDialogueStyle::SEQUENCE:
	{
		UDialogue_Sequence* Dialogue = Cast<UDialogue_Sequence>(DialogueSet.DialogueList[SetIndex]);
		if (Dialogue)
		{
			UM3GameInstance::GetCinematicSystem()->PlayCinema(Dialogue->Name);
		}
	}
	break;
	case EDialogueStyle::BEGIN_QUEST:
	{
		UDialogue_BeginQuest* Dialogue = Cast<UDialogue_BeginQuest>(DialogueSet.DialogueList[SetIndex]);
		if (Dialogue)
		{
			UM3GameInstance::GetQuestSystem()->QuestActivate(Dialogue->Index);
		}
		Next();
	}
	break;
	case EDialogueStyle::QUEST_COMPLETE:
	{
		UDialogue_QuestComplete* Dialogue = Cast<UDialogue_QuestComplete>(DialogueSet.DialogueList[SetIndex]);
		if (Dialogue)
		{
			UM3GameInstance::GetQuestSystem()->QuestComplete(Dialogue->Index);
		}
		Next();
	}
	break;
	default:
		break;
	}
	return true;
}

void UDialogueWidget::Choice(int Index)
{
	if (Index == -1) Index = FocusIndex;
	FDialogueSet DialogueSet;
	if (UM3GameInstance::GetDialogueSystem()->GetDialogueSet(DialogueSet, ChoiceList[Index]->JumpingIndex))
	{
		ChoiceList.Empty();
		VerticalBox->ClearChildren();
		SetDialogue(DialogueSet);
	}
}

void UDialogueWidget::End()
{
	ChoiceList.Empty();
	VerticalBox->ClearChildren();
	UUIMainWidget::GetInstance()->ShowDefualtUI();
}