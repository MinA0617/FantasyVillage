#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWidget.generated.h"

UCLASS()
class M3PROJECT_API UOptionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable) void SaveGame();
	UFUNCTION(BlueprintCallable) void ReturnTitle();
	// void Volume();
};
