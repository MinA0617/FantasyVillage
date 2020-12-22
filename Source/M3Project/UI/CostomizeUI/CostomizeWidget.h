#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ModelCenter/Character/Base/CostomizeCharacter.h"
#include "Components/ScrollBox.h"
#include "Components/Slider.h"
#include "CheckBox.h"
#include "Engine/DataTable.h"
#include "CostomizeColorItem.h"
#include "CostomizeIndexItem.h"
#include "CostomizeWidget.generated.h"

const int kCostomizeItemRowCount = 5;

UENUM(blueprinttype)
enum class EScalraType : uint8
{
	EyeHeight,
	EyeInterval,
	EyeSize,
	EyeRoation,
	EyeStretch,
	EyebrowHeight,
	EyebrowInterval,
	EyebrowSize,
	EyebrowRoation,
	EyebrowStretch,
	MouseHeight,
	MouseSize,
	MouseStretch,
	NoseHeight,
	NoseSize,
	NoseStretch,
};

UCLASS()
class M3PROJECT_API UCostomizeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UCostomizeWidget(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)	TArray<UCostomizeColorPage*> ColorPageList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TArray<UCostomizeIndexPage*> IndexPageList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TArray<USlider*> SliderList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UCheckBox* MaleBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UCheckBox* FemaleBox;
	ACostomizeCharacter*	Owner;
public:
	void NativeConstruct() override;
	void SetOwner(ACostomizeCharacter* owner);
	ACostomizeCharacter* GetOwner() { return Owner; };
	UFUNCTION(BlueprintCallable) void ModifyColorParma(EColorType Type, FColor Color);
	UFUNCTION(BlueprintCallable) void ModifyIndexParma(EIndexType Type, int Index);
	UFUNCTION(BlueprintCallable) void ModifyScalarParma(EScalraType Type, float Value);
	UFUNCTION(BlueprintCallable) void ModifySex(bool IsFemale);
	UFUNCTION() void LoadingComplete();
private:
	int LoadCount;
	UDataTable* PalleteDataTable;
};

USTRUCT(BlueprintType)
struct FCostomizeColorPalleteResource : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		EColorType Type;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FColor Color;
};