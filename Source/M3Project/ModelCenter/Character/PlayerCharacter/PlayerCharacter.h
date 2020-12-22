#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/Base/CostomizeCharacter.h"
#include "ModelCenter/Character/PlayerCharacter/FiniteStateMachine/PlayerFiniteStateMachine.h"
#include "PlayerCharacter.generated.h"

USTRUCT(BlueprintType)
struct FHelperComponent
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() USkeletalMeshComponent* HelperMesh;
	UPROPERTY() UStaticMeshComponent* ObjectMesh;
};

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() FName	CharacterName;
	UPROPERTY() FVector PlayerLocation;
	UPROPERTY() int		MaxHP;
	UPROPERTY() int		CurrentHP;
	UPROPERTY() int		AttackPoint;
	UPROPERTY() int		DeffensPoint;
};

UCLASS()
class M3PROJECT_API APlayerCharacter : public ACostomizeCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
private:
	FPlayerInfo					PlayerInfo;
public:
	UPROPERTY()	UPlayerFiniteStateMachine*	PlayerFiniteStateMachine;
	UPROPERTY() UCapsuleComponent*			SlashWeaponCollisonComponent;
	UPROPERTY() FHelperComponent			HelperComponent;
public:
	float	MagnificationValue;
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
public:
	void ReBuildStatFromItem();
	void ApplyDamage(int Damage, ACharacter* Attacker);
	void SetWeaponLength(float Length);
	void ChangeBattleMode(bool OnOff);
	UWeaponItem* ChangeWeaponItem(UWeaponItem* Item);
	UEquipmentItem* ChangeEquipmentItem(UEquipmentItem* Item, EEquipmentsType Type);
	FPlayerInfo& GetPlayerInfo();
	void SetPlayerInfo(FPlayerInfo& Info);
public:
	void Turn(float Value);
	void LookUp(float Value);
public:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MouseWheel(float Value);
	void MouseLeftClick();
	void MouseRightClick();
	void MouseLeftRelease();
	void MouseRightRelease();
	void BattleOn();
	void BuildOn();
	void JumpAction();
	void Menu();
	void Enter();
public:
	void ShowEditorWidget();
};
