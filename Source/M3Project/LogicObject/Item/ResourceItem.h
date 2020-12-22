#pragma once

#include "CoreMinimal.h"
#include "LogicObject/Item/Base/ItemBase.h"
#include "ResourceItem.generated.h"

USTRUCT(BlueprintType)
struct FResourceDefaultInfo
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
		FString ToolTip;
};

UCLASS()
class M3PROJECT_API UResourceItem : public UItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FResourceDefaultInfo DefaultInfo;
public:
	virtual EItemType GetType() override { return EItemType::RESOURCE; };
	virtual bool Use() override { return false; };
	virtual int GetID() override { return DefaultInfo.ID; };
	virtual int GetIconID() { return DefaultInfo.IconResource; };
	virtual FString GetItemName() { return DefaultInfo.Name; };
	
};

USTRUCT(BlueprintType)
struct FResourceItemTableResource : public FTableRowBase
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
		FString ToolTip;
};