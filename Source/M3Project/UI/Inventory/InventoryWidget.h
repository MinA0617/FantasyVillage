#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LogicObject/Item/ItemManager.h"
#include "InventoryPageWidget.h"
#include "GameHandler/Inventory/Inventory.h"
#include "InvenCharacterStateWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class M3PROJECT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventoryPageWidget* Page_Weapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventoryPageWidget* Page_Equipment;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventoryPageWidget* Page_Consumption;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventoryPageWidget* Page_Resource;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventoryPageWidget* Page_Installation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInvenCharacterStateWidget* StateWidget;
public:
	void NativeConstruct() override;
	UFUNCTION(BlueprintCallable) void UseItem(EItemType Type, int Index);
	UFUNCTION(BlueprintCallable) void ReBuild();
};
