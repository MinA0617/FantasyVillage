// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Helper.h"
#include "UObject/NoExportTypes.h"
#include "PlayerFiniteState.generated.h"

class APlayerCharacter;

UENUM()
enum class EPlayerState : uint8
{
	DEFUALT,
	BATTLE,
	ATTACK,
	BUILD,
	DEFUALT_REACT,
	REACT,
	BUILD_REACT,
	DIALOGUE,
	DEAD,
	__MAX__,
};

UENUM()
enum class EPlayerEvent : uint8
{
	RETURN_DEFUALT,
	BATTLE_START,
	ATTACK_START,
	BUILD_START,
	REACT_START,
	DEAD_START,
	DIALOGUE_START,
};

UCLASS()
class M3PROJECT_API UPlayerFiniteState : public UObject
{
	GENERATED_BODY()
public:
	EPlayerState State;
	UPROPERTY() APlayerCharacter* Target;
	virtual void Init(APlayerCharacter* target) { Target = target; };
	virtual void Release() {};
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
	virtual void MouseLeftClick() {};
	virtual void MouseRightClick() {};
	virtual void MouseLeftRelease() {};
	virtual void MouseRightRelease() {};
	virtual void MouseWheel(float Value);
	virtual void BattleOn() {};
	virtual void BuildOn() {};
	virtual void JumpAction();
	virtual void Enter() {};
	virtual void Tick(float DeltaSecond) {};
};