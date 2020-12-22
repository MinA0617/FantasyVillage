#pragma once

#include "CoreMinimal.h"
#include "Base/ItemBase.h"
#include "ConsumptionItem.generated.h"

USTRUCT(BlueprintType)
struct FConsumptionDefaultInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 ID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 IconResource;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 RecoveryHP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString ToolTip;
};

UCLASS()
class M3PROJECT_API UConsumptionItem : public UItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FConsumptionDefaultInfo DefaultInfo;
public:
	virtual EItemType GetType() override { return EItemType::CONSUMPTION; };
	virtual bool Use() override { return false; };
	virtual int GetID() override { return DefaultInfo.ID; };
	virtual int GetIconID() { return DefaultInfo.IconResource; };
	virtual FString GetItemName() { return DefaultInfo.Name; };
	
};

USTRUCT(BlueprintType)
struct FConsumptionItemTableResource : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 IconResource;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 RecoveryHP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString ToolTip;
};