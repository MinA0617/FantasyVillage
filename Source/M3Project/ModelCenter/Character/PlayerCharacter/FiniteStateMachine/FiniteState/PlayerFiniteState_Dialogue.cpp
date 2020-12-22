#include "PlayerFiniteState_Dialogue.h"
#include "UI/UIMainWidget.h"

void UPlayerFiniteState_Dialogue::Init(APlayerCharacter* target)
{
	Target = target;
}

void UPlayerFiniteState_Dialogue::Release()
{
	UUIMainWidget::GetInstance()->DialogueWidget->End();
}

void UPlayerFiniteState_Dialogue::MouseLeftClick()
{
	if (UUIMainWidget::GetInstance()->DialogueWidget->Next() == false)
	{
		Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::RETURN_DEFUALT);
	}
}

void UPlayerFiniteState_Dialogue::MoveForward(float Value)
{
	if (Value > 0.1f)
	{
		UUIMainWidget::GetInstance()->DialogueWidget->FocusChoiceNext(false);
	}
	else if (Value < -0.1f)
	{
		UUIMainWidget::GetInstance()->DialogueWidget->FocusChoiceNext(true);
	}
}

void UPlayerFiniteState_Dialogue::Enter()
{
	UUIMainWidget::GetInstance()->DialogueWidget->Choice();
}