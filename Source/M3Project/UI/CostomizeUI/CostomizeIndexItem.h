#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "CostomizeIndexItem.generated.h"

class UCostomizeWidget;

UENUM(blueprinttype)
enum class EIndexType : uint8
{
	HeadID,
	HairID,
	EyeID,
	EyebrowID,
	MouseID,
	NoseID,
	EarsID,
};

UCLASS()
class M3PROJECT_API UCostomizeIndexItem : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)	int						Index;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UCostomizeIndexPage*	Parent;
public:
	UFUNCTION(BlueprintImplementableEvent)	void SetTextrue(UTexture* Tex);
	UFUNCTION(BlueprintImplementableEvent)	void SetTextrue_Sub(UTexture* Tex);
};

UCLASS()
class M3PROJECT_API UCostomizeIndexPage : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TSubclassOf<UCostomizeIndexItem> CostomizeIndexItemClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) TArray<UCostomizeIndexItem*> IndexItemList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UCostomizeWidget* Parent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UUniformGridPanel* UniformGridPanel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) EIndexType Type;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) UImage* FouceImage;
public:
	void SetMember(int Index);
	UFUNCTION(BlueprintCallable) void SetFocus(int Index);
};