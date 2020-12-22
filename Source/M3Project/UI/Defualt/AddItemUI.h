#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LogicObject/Item/Base/ItemBase.h"
#include "AddItemUI.generated.h"

UCLASS()
class M3PROJECT_API UAddItemUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct();
public:
	UUserWidget* ParentWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	UWidgetAnimation* InitAnimation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UTexture2D* Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FString ItemName;
	FWidgetAnimationDynamicEvent EndEvent;
public:
	void SetItemAndStart(UUserWidget* Parent, UItemBase* Item);
	UFUNCTION(BlueprintImplementableEvent) void Rebuild();
	UFUNCTION(BlueprintCallable) void EndAnimation();
	UFUNCTION(BlueprintCallable) void End();
};
