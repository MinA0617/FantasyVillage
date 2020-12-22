// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/PlayerCharacter/FiniteStateMachine/FiniteState/PlayerFiniteState.h"
#include "GameFramework/Character.h"
#include "PlayerFiniteState_DefualtReact.generated.h"

/**
 * 
 */
UCLASS()
class M3PROJECT_API UPlayerFiniteState_DefualtReact : public UPlayerFiniteState
{
	GENERATED_BODY()
public:
	UPlayerFiniteState_DefualtReact() { State = EPlayerState::DEFUALT_REACT; };
public:
	void Init(APlayerCharacter* target) override;
	void Release() override;
	void MoveForward(float Value) {};
	void MoveRight(float Value) {};
	void MouseLeftClick() {};
	void MouseRightClick() {};
	void BattleOn() {};
	void JumpAction() {};
	void React(ACharacter* Attacker);
	UFUNCTION() void ReactEnd(UAnimMontage* Montage, bool bInterrupted);
private:
	int ReactCount;
	bool bIsDown;
};
