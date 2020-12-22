#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "InventorySlotWidget.h"
#include "GameHandler/Inventory/Inventory.h"
#include "InventoryPageWidget.generated.h"

const int kHorizonSize = 5;

UCLASS()
class M3PROJECT_API UInventoryPageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UUserWidget* ParentWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TSubclassOf<UInventorySlotWidget> SlotClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UUniformGridPanel* UniformGridPanel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<UInventorySlotWidget*> SlotList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool bShowCount;
public:
	UFUNCTION(BlueprintCallable) void AddItem(UItemBase* Item, int Count = 1);
	UFUNCTION(BlueprintCallable) void Clear();
private:
	int ItemCount;
};
