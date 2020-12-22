#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueChoiceWidget.generated.h"

UCLASS()
class M3PROJECT_API UDialogueChoiceWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere) UUserWidget* ParentWidget;
    UPROPERTY(BlueprintReadWrite, EditAnywhere) int ChoiceIndex;
    int JumpingIndex;
public:
    UFUNCTION(BlueprintCallable) void Choice();
    UFUNCTION(BlueprintImplementableEvent) void SetString(FString const& TextPam);
    UFUNCTION(BlueprintImplementableEvent) void SetFocus(bool bIsTrue);
};
