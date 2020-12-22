#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/CostomizeUI/CostomizeWidget.h"
#include "CharacterCreateWidget.generated.h"

const int kMaxCharacterName = 12;

UCLASS()
class M3PROJECT_API UCharacterCreateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UCostomizeWidget* CostomizeWidget;
	FString CharacterName;
public:
	UFUNCTION(BlueprintCallable) void CreateCharacter();
	UFUNCTION(BlueprintCallable) FString SetCharacterName(FString NewCharacterName);
};
