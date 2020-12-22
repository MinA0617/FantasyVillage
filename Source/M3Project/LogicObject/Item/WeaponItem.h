#pragma once

#include "CoreMinimal.h"
#include "LogicObject/Item/Base/ItemBase.h"
#include "WeaponItem.generated.h"

UENUM()
enum class EWeaponType : uint8
{
	NONE = 0,
	TWOHANDED = 1,
};

USTRUCT(BlueprintType)
struct FWeaponDefaultInfo
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
		int32 SubType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 WeaponLenght;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 AttackPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString ToolTip;
};

//USTRUCT(BlueprintType)
//struct FWeaponData
//{
//	GENERATED_USTRUCT_BODY()
//public:
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
//		int32 ID;
//};


UCLASS()
class M3PROJECT_API UWeaponItem : public UItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FWeaponDefaultInfo DefaultInfo;
public:
	virtual EItemType GetType() override { return EItemType::WEAPON; };
	virtual bool Use() override { return false; };
	virtual int GetID() override { return DefaultInfo.ID; };
	virtual int GetIconID() { return DefaultInfo.IconResource; };
	virtual FString GetItemName() { return DefaultInfo.Name; };
	bool IsTwohanded();
};

USTRUCT(BlueprintType)
struct FWeaponItemTableResource : public FTableRowBase
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
		int32 WeaponLenght;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 AttackPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString ToolTip;
};
