#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHandler/DialogueSystem/DialogueSystem.h"
#include "DialogueChoiceWidget.h"
#include "Components/VerticalBox.h"
#include "DialogueWidget.generated.h"

UCLASS()
class M3PROJECT_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	TSubclassOf<UDialogueChoiceWidget> ChoiceWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UVerticalBox* VerticalBox;
	UPROPERTY() TArray<UDialogueChoiceWidget*> ChoiceList;
	void SetDialogue(FDialogueSet& NewDialogueSet);
	void Choice(int Index = -1);
	void FocusChoiceNext(bool bIsNext);
	bool Next();
	void End();
	UPROPERTY() FDialogueSet DialogueSet;
	UFUNCTION(BlueprintCallable) void FocusChoice(int Index);
public:
	UFUNCTION(BlueprintImplementableEvent) void SetString(FString const& TextPam);
	UFUNCTION(BlueprintImplementableEvent) void NextString(FString const& TextPam);
private:
	int SetIndex;
	int FocusIndex;
};
