#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.h"
#include "Components/TextBlock.h"
#include "InvenCharacterStateWidget.generated.h"

UCLASS()
class M3PROJECT_API UInvenCharacterStateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UTextBlock* TextTitle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UTextBlock* TextToolTip;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* SlotWeapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* SlotTop;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* SlotBottom;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* SlotHands;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* SlotFeet;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* SlotCap;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventorySlotWidget* SlotToolTip;
	UUserWidget* ParentWidget;
public:
	void ParentSet();
	void SetWeapon(UWeaponItem* WeaponItem);
	void SetEquipment(EEquipmentsType Type, UEquipmentItem* EquipmentItem);
	UFUNCTION(BlueprintCallable) void SetPopupItem(UItemBase* ToolTipItem);
	
};
