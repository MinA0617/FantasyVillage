// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "ItemWidgetPage.generated.h"

/**
 * 
 */
UCLASS()
class M3PROJECT_API UItemWidgetPage : public UUserWidget
{
	GENERATED_BODY()
public:
	UItemWidgetPage(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUniformGridPanel* UnifomGrid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UUserWidget*> UniformList;
	int32 HorizonCount;
	int32 PaddingSize;
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetMember();
	void SetUnifom();
	void AddItem(UUserWidget* item);
};
