// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CostomizeCharacter.h"
#include "Engine/DataTable.h"
#include "CostomizeManager.generated.h"

const int kScalaValueSize = 16;

UENUM()
enum class ECostomizeParts : uint8
{
	EyebrowHeight,
	EyebrowInterval,
	EyebrowSize,
	EyebrowRoation,
	EyebrowStretch,
	EyeHeight,
	EyeInterval,
	EyeSize,
	EyeRoation,
	EyeStretch,
	MouseHeight,
	MouseSize,
	MouseStretch,

	NoseHeight,
	NoseSize,
	NoseStretch,

	HeadID,
	HairID,
	NoseID,
	EarsID,
	EyeID,
	EyebrowID,
	MouseID,

	SkinColor,
	EyeborwColor,
	EyeColor,
	MouseColor,
	HairColor,
};

struct FValueMinMax
{
	FValueMinMax() {};
	FValueMinMax(float min, float max)
	{
		Min = min;
		Max = max;
	};
	float Min;
	float Max;
};


UCLASS()
class M3PROJECT_API UCostomizeManager : public UObject
{
	GENERATED_BODY()
public:
	UCostomizeManager();
public:
	void Init();
	void SetCostomize(ACostomizeCharacter* owner);
	void ModifyCostomizeScalaValue(ACostomizeCharacter* owner, ECostomizeParts name, float value);
	void ModifyCostomizeTextureValue(ACostomizeCharacter* owner, ECostomizeParts name, int id);
	void ModifyCostomizeColorValue(ACostomizeCharacter* owner, ECostomizeParts name, FColor color);
	void ModifyCostomizeSex(ACostomizeCharacter* owner, bool IsFemale);
	TArray<TArray<int>>& GetCostomizeItemList(ECostomizeType Type);
private:
	FValueMinMax MinMaxList[kScalaValueSize];
	float ConvertValue(ECostomizeParts name, float value);
	TArray<TArray<TArray<int>>> CostomizeItemList;
};

UENUM()
enum class ECostomizeType : uint8
{
	EYES,
	EYEBROW,
	MOUSE,
	EARS,
	NOSE,
	HEAD,
	HAIR,
};

USTRUCT(BlueprintType)
struct FCostomizeItemResource : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
		ECostomizeType Type;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
		int32 ResourceIconID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
		int32 ResourceMeshID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info")
		int32 ResourceSubID;
};