// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ModelCenter/Character/Base/CostomizeManager.h"
#include "Components/Slider.h"
#include "Components/HorizontalBox.h"
#include "TextBlock.h"
#include "CostomizeSlide.generated.h"

class UCostomizeWidget;

UCLASS()
class M3PROJECT_API UCostomizeSlide : public UUserWidget
{
	GENERATED_BODY()
public:
	UCostomizeWidget*	Parent;
	ECostomizeParts		PartsName;
	FText				Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTextBlock*			NameBox;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USlider*			Slider;
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetMember();
	UFUNCTION(BlueprintCallable)
	void Set(UCostomizeWidget* parent, ECostomizeParts name, FString hanglename);
	UFUNCTION(BlueprintCallable)
	void ModifyValue(float value);
};
