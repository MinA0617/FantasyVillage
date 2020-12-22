// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragAndDropOperation.h"
#include "HorizontalBox.h"
#include "HorizontalBoxSlot.h"
#include "TextBlock.h"
#include "Button.h"
#include "DragWidget.generated.h"

/**
 * 
 */
UCLASS()
class M3PROJECT_API UDragWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UDragWidget(const FObjectInitializer& ObjectInitializer);
public:
	void Set(FName titlename, UUserWidget* ownerwidget, int(*exitpointer)());
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
public:
	FName TitleName;
	FVector2D DragOffset;
	UUserWidget* OwnerWidget;
	int(*ExitPointer)();
public:
	UHorizontalBox* HorizontalBox;
	UTextBlock* NameTextBlock;
	UButton* ExitButton;
public:

};
