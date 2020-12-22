#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHandler/Inventory/Inventory.h"
#include "InventorySlotWidget.generated.h"


UCLASS()
class M3PROJECT_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	EItemType ItemType;
	int SlotIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UItemBase* Item;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UTexture2D* Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int32 ItemCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool bShowCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UUserWidget* GrandParentWidget;
public:
	int IconID;
	UFUNCTION(BlueprintCallable) void SetIcon();
	UFUNCTION(BlueprintCallable) virtual void UseItem();
	UFUNCTION(BlueprintImplementableEvent) void Rebuild();
};

UCLASS()
class M3PROJECT_API UInventorySlotStateWidget : public UInventorySlotWidget
{
	GENERATED_BODY()
public:
	void UseItem() override;
};