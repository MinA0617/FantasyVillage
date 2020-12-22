// Fill out your copyright notice in the Description page of Project Settings.


#include "DragAndDropOperation.h"

void UDragAndDropOperation::Set(UUserWidget* userwidget, FVector2D dragoffset)
{
	OwnerWidget = userwidget;
	DragOffset = dragoffset;
}