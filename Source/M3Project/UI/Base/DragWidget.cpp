// Fill out your copyright notice in the Description page of Project Settings.


#include "DragWidget.h"
#include "WidgetTree.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Input/Reply.h"


UDragWidget::UDragWidget(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	WidgetTree = CreateDefaultSubobject<UWidgetTree>(TEXT("WidgetTree"));
	WidgetTree->SetFlags(RF_Transactional);
	HorizontalBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
	NameTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	ExitButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());

	WidgetTree->RootWidget = HorizontalBox;
	HorizontalBox->AddChild(NameTextBlock);
	HorizontalBox->AddChild(ExitButton);

	UHorizontalBoxSlot* NameTextBlockSlot = Cast<UHorizontalBoxSlot>(NameTextBlock->Slot);
	UHorizontalBoxSlot* ExitButtonSlot = Cast<UHorizontalBoxSlot>(ExitButton->Slot);
	if (NameTextBlockSlot)
	{
		NameTextBlockSlot->Padding = FMargin(12.0f);
		NameTextBlockSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Left;
		NameTextBlockSlot->Size.SizeRule = ESlateSizeRule::Fill;
		NameTextBlockSlot->Size.Value = 1.0f;
	}
	if (ExitButtonSlot)
	{
		ExitButtonSlot->Padding = FMargin(8.0f);
		ExitButtonSlot->HorizontalAlignment = EHorizontalAlignment::HAlign_Right;
		ExitButtonSlot->Size.SizeRule = ESlateSizeRule::Fill;
		ExitButtonSlot->Size.Value = 1.0f;
	}

	//FButtonStyle ExitButtonStyle;
	//FSlateBrush NormalBrush;
	//ExitButtonStyle.SetNormal(NormalBrush);
	//ExitButtonStyle.SetHovered(NormalBrush);
	//ExitButtonStyle.SetPressed(NormalBrush);
	//ExitButtonStyle.SetDisabled(NormalBrush);
	//ExitButton->SetStyle(ExitButtonStyle);
}

void UDragWidget::Set(FName titlename, UUserWidget* ownerwidget, int(*exitpointer)())
{
	TitleName = titlename;
	OwnerWidget = ownerwidget;
	ExitPointer = exitpointer;
}

FReply UDragWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}


void UDragWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	UDragAndDropOperation* DragAndDropOperation = NewObject<UDragAndDropOperation>();
	DragAndDropOperation->Set(OwnerWidget, DragOffset);
	DragAndDropOperation->Pivot = EDragPivot::MouseDown;
	OwnerWidget->RemoveFromParent();
	OutOperation = DragAndDropOperation;
}
