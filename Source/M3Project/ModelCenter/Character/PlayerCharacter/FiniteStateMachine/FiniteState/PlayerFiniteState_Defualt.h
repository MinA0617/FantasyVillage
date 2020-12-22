// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/PlayerCharacter/FiniteStateMachine/FiniteState/PlayerFiniteState.h"
#include "PlayerFiniteState_Defualt.generated.h"

/**
 * 
 */
UCLASS()
class M3PROJECT_API UPlayerFiniteState_Defualt : public UPlayerFiniteState
{
	GENERATED_BODY()
public:
    UPlayerFiniteState_Defualt() { State = EPlayerState::DEFUALT; }
public:
    void Init(APlayerCharacter* target) override;
    void MouseLeftClick() override;
    void BattleOn() override;
    void BuildOn() override;
public:
    UFUNCTION() void ChangeEnd(UAnimMontage* Montage, bool bInterrupted);
private:
    bool IsChanging;
};
