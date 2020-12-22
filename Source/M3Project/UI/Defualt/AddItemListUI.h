#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AddItemUI.h"
#include "Components/VerticalBox.h"
#include "AddItemListUI.generated.h"

UCLASS()
class M3PROJECT_API UAddItemListUI : public UUserWidget
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)	UWidgetAnimation* InitAnimation;
    UPROPERTY(BlueprintReadWrite, EditAnywhere) TSubclassOf<UAddItemUI> AddItemClass;
    UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<UAddItemUI*> AddItemList;
    UPROPERTY(BlueprintReadWrite, EditAnywhere) UVerticalBox* VBox;
public:
    void AddAddItemWidget(UItemBase* Item);
    void RemoveAddItemWidget();
    void TimerOut();
private:
    bool IsNextAnimation;
    FTimerHandle Timer[3];
};
