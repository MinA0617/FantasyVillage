#pragma once

#include "CoreMinimal.h"
#include "LogicObject/Item/Base/ItemBase.h"
#include "InstallationItem.generated.h"

UENUM()
enum class EInstallationType : uint8
{
	CUBE = 0,
	GRASS = 1,
};

USTRUCT(BlueprintType)
struct FInstallationDefaultInfo
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
		int32 MeshResource;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 Type;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		EInstallationType SubType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString ToolTip;
};

UCLASS()
class M3PROJECT_API UInstallationItem : public UItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FInstallationDefaultInfo DefaultInfo;
public:
	virtual EItemType GetType() override { return EItemType::INSTALLATION; };
	virtual bool Use() override { return false; };
	virtual int GetID() override { return DefaultInfo.ID; };
	virtual int GetIconID() { return DefaultInfo.IconResource; };
	virtual FString GetItemName() { return DefaultInfo.Name; };
	
};

USTRUCT(BlueprintType)
struct FInstallationItemTableResource : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 IconResource;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 MeshResource;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 Type;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 SubType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString ToolTip;
};