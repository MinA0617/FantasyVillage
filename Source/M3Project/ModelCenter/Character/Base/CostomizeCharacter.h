#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/SkeletalMesh.h"
#include "LogicObject/Item/EquipmentItem.h"
#include "LogicObject/Item/WeaponItem.h"
#include "Resource/M3ResourceManager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ModelCenter/Character/PlayerCharacter/Animation/PlayerAnimInstance.h"
#include "CostomizeCharacter.generated.h"

const int kTopNude = 10000011;
const int kBottomNude = 10000012;
const int kHandsNude = 10000013;
const int kFeetNude = 10000014;
const int kTopNude_F = 10000021;
const int kBottomNude_F = 10000022;

USTRUCT(BlueprintType)
struct FPartsComponent
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() UStaticMeshComponent* HeadComponent;
	UPROPERTY() UStaticMeshComponent* EarsComponent;
	UPROPERTY() UStaticMeshComponent* NoseComponent;
	UPROPERTY() UStaticMeshComponent* HairComponent;
	UPROPERTY() UStaticMeshComponent* CapComponent;
	UPROPERTY() UStaticMeshComponent* WeaponComponent;
	UPROPERTY() UStaticMeshComponent* SubWeaponComponent;
	UPROPERTY() USkeletalMeshComponent* TopComponent;
	UPROPERTY() USkeletalMeshComponent* BottomComponent;
	UPROPERTY() USkeletalMeshComponent* HandsComponent;
	UPROPERTY() USkeletalMeshComponent* FeetComponent;
};

USTRUCT(BlueprintType)
struct FCustomizingInformation
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() bool	IsFemale;
	UPROPERTY() FColor	SkinColor;
	UPROPERTY() int64	HeadID;
	UPROPERTY() int64	HairID;
	UPROPERTY() FColor	HairColor;
	UPROPERTY() int64	EyeID;
	UPROPERTY() FColor	EyeColor;
	UPROPERTY() float	EyeHeight;
	UPROPERTY() float	EyeInterval;
	UPROPERTY() float	EyeSize;
	UPROPERTY() float	EyeRoation;
	UPROPERTY() float	EyeStretch;
	UPROPERTY() int64	EyebrowID;
	UPROPERTY() FColor	EyeborwColor;
	UPROPERTY() float	EyebrowHeight;
	UPROPERTY() float	EyebrowInterval;
	UPROPERTY() float	EyebrowSize;
	UPROPERTY() float	EyebrowRoation;
	UPROPERTY() float	EyebrowStretch;
	UPROPERTY() int64	MouseID;
	UPROPERTY() FColor	MouseColor;
	UPROPERTY() float	MouseHeight;
	UPROPERTY() float	MouseSize;
	UPROPERTY() float	MouseStretch;
	UPROPERTY() int64	NoseID;
	UPROPERTY() float	NoseHeight;
	UPROPERTY() float	NoseSize;
	UPROPERTY() float	NoseStretch;
	UPROPERTY() int64	EarsID;
};

USTRUCT(BlueprintType)
struct FEquipment
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() UWeaponItem* WeaponItem;
	UPROPERTY() UEquipmentItem* CapItem;
	UPROPERTY() UEquipmentItem* TopItem;
	UPROPERTY() UEquipmentItem* BottomItem;
	UPROPERTY() UEquipmentItem* HandsItem;
	UPROPERTY() UEquipmentItem* FeetItem;
};

UCLASS()
class M3PROJECT_API ACostomizeCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ACostomizeCharacter(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY() UCameraComponent* CameraComponent;
	UPROPERTY() USpringArmComponent* SpringArmComponent;
	UPROPERTY() FCustomizingInformation CostomizingInformation;
	UPROPERTY() FPartsComponent CharacterPartsComponent;
	UPROPERTY() FEquipment EquipmentItem;
	EWeaponType CurrentWeaponType;
protected:
	virtual void BeginPlay() override;
public:
	void SetAnimation(UClass* AnimClass);
	UAnimInstance* GetAnimation();
	void ApplyGravity(bool is_ture);
	void SetupSex(bool isFemale);
};