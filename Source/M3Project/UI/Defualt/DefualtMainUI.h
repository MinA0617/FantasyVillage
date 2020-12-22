#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AddItemListUI.h"
#include "StateBarUI.h"
#include "DefualtMainUI.generated.h"

UCLASS()
class M3PROJECT_API UDefualtMainUI : public UUserWidget
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        UStateBarUI* StateBar;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        UAddItemListUI* AddItemList;
};
