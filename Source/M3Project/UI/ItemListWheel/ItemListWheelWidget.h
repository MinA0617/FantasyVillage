#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHandler/Inventory/Inventory.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "ItemListWheelWidget.generated.h"

UCLASS()
class M3PROJECT_API UItemListWheelWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* Slot01;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* Slot02;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* Slot03;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* Slot04;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* Slot05;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* Slot06;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* Slot07;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	UWidgetAnimation* RightMoveAni;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	UWidgetAnimation* LeftMoveAni;
	UPROPERTY() TArray<FWidgetTransform> WidgetTransformList;
public:
	void NativeConstruct() override;
public:
	void SetList(EItemType Type, int Index);
	bool NextIndex();
	bool PrevIndex();
	UFUNCTION() void SetListFromIndex();
private:
	FWidgetAnimationDynamicEvent REndEvent;
	FWidgetAnimationDynamicEvent LEndEvent;
	EItemType CurrentType;
	int CurrentIndex;
	bool IsPlayAnimation;
};
