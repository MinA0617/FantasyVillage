// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "CostomizeColorItem.generated.h"

class UCostomizeWidget;

UENUM(blueprinttype)
enum class EColorType : uint8
{
	SkinColor,
	HairColor,
	EyeColor,
	EyeborwColor,
	MouseColor,
};

UCLASS()
class M3PROJECT_API UCostomizeColorItem : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)	int						Index;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UCostomizeColorPage*	Parent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UBorder*				Border;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) FColor					Color;
public:
	void SetColor(FColor SetUpColor);
};

UCLASS()
class M3PROJECT_API UCostomizeColorPage : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TSubclassOf<UCostomizeColorItem> CostomizeColorItemClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TArray<UCostomizeColorItem*> ColorItemList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UCostomizeWidget* Parent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UUniformGridPanel* UniformGridPanel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) EColorType Type;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UImage* FouceImage;
public:
	void AddColorItem(FColor Color);
	UFUNCTION(BlueprintCallable) void SetFocus(int Index);
};