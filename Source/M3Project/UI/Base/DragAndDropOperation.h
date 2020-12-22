// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/UserWidget.h"
#include "DragAndDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class M3PROJECT_API UDragAndDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UFUNCTION()
		void Set(UUserWidget* userwidget, FVector2D dragoffset);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UUserWidget* OwnerWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FVector2D DragOffset;
};
