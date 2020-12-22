#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemBase.generated.h"

UENUM()
enum class EItemType : uint8
{
	NONE,
	RESOURCE,
	CONSUMPTION,
	EQUIPMENT,
	WEAPON,
	INSTALLATION,
};

UCLASS()
class M3PROJECT_API UItemBase : public UObject
{
	GENERATED_BODY()
public:
	EItemType ItemType;
public:
	UFUNCTION(BlueprintCallable, Category = "C_Function")
		virtual EItemType GetType() { return EItemType::NONE; };
	UFUNCTION(BlueprintCallable, Category = "C_Function")
		virtual bool Use() { return false; };
	UFUNCTION(BlueprintCallable, Category = "C_Function")
		virtual int GetID() { return -1; };
	UFUNCTION(BlueprintCallable, Category = "C_Function")
		virtual int GetIconID() { return -1; };
	UFUNCTION(BlueprintCallable, Category = "C_Function")
		virtual FString GetItemName() { return FString(); };
};