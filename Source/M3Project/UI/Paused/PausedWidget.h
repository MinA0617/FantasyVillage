#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanel.h"
#include "../Inventory/InventoryWidget.h"
#include "PausedWidget.generated.h"

UCLASS()
class M3PROJECT_API UPausedWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	UWidgetAnimation*		RightMoveAni;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	UWidgetAnimation*		LeftMoveAni;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	USizeBox*				LeftBox;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	USizeBox*				MiddleBox;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	USizeBox*				RightBox;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) UCanvasPanel*			SaveCanvasPanel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	TArray<UUserWidget*>	PageWidgets;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	UUserWidget*			CurrentPageWidget;
public:
	UFUNCTION(BlueprintCallable) void AddPage(UUserWidget* TargetWidget);
	UFUNCTION(BlueprintCallable) void PageMove(int PageIndex);
	UFUNCTION(BlueprintCallable) void PageNext(bool bIsNext);
	UFUNCTION(BlueprintCallable) void ReturnGame();
public:
	UFUNCTION(BlueprintCallable) void NextEndFunction();
	UFUNCTION(BlueprintCallable) void PrevEndFunction();
	UFUNCTION(BlueprintCallable) void Build();
private:
	int CurrentIndex;
	FWidgetAnimationDynamicEvent LeftEndEvent;
	FWidgetAnimationDynamicEvent RightEndEvent;
	bool IsPlayAnimation;
};
