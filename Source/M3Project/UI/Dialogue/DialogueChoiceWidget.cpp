#include "DialogueChoiceWidget.h"
#include "DialogueWidget.h"

void UDialogueChoiceWidget::Choice()
{
	Cast<UDialogueWidget>(ParentWidget)->Choice(ChoiceIndex);
}