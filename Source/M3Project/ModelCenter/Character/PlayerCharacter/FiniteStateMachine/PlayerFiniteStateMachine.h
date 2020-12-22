// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FiniteState/PlayerFiniteState.h"
#include "PlayerFiniteStateMachine.generated.h"

UCLASS()
class M3PROJECT_API UPlayerFiniteStateMachine : public UObject
{
	GENERATED_BODY()
public:
	UPlayerFiniteStateMachine(const FObjectInitializer& ObjectInitializer);
public:
	UPlayerFiniteState* CurrentPlayerState;
private:
	TMap<EPlayerState, TMap<EPlayerEvent, EPlayerState>> StateMachineList;
	UPROPERTY()	TArray<UPlayerFiniteState*> PlayerFiniteStateList;
	UPROPERTY() APlayerCharacter* Owner;
public:
	void AddFiniteState(EPlayerState state, EPlayerEvent stateevent, EPlayerState nextstate);
	void StateEvent(EPlayerEvent Event);
public:
	void Init(APlayerCharacter* owner);
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MouseLeftClick();
	void MouseRightClick();
	void MouseLeftRelease();
	void MouseRightRelease();
	void MouseWheel(float Value);
	void JumpAction();
	void BattleOn();
	void BuildOn();
	void Enter();
	void Tick(float DeltaSecond);
};