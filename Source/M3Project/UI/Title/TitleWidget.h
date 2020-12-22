#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Resource/SaveData/SaveManager.h"
#include "TitleWidget.generated.h"

UCLASS()
class M3PROJECT_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    void NativeConstruct() override;
    UFUNCTION(BlueprintCallable) void           Exit();
    UFUNCTION(BlueprintCallable) bool           CreateNewGame(int Index);
    UFUNCTION(BlueprintCallable) bool           LoadGame(int Index);
    UFUNCTION(BlueprintCallable) bool           DeleteGame(int Index);
    UFUNCTION(BlueprintCallable) FGameSlotData  GetSlotData(int Index);
    UFUNCTION(BlueprintCallable) void           EditorMode();
    UFUNCTION(BlueprintCallable) void           NewEditData();
};
