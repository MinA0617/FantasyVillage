// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/PlayerCharacter/FiniteStateMachine/FiniteState/PlayerFiniteState.h"
#include "PlayerFiniteState_Dead.generated.h"

/**
 * 
 */
UCLASS()
class M3PROJECT_API UPlayerFiniteState_Dead : public UPlayerFiniteState
{
	GENERATED_BODY()
public:
	UPlayerFiniteState_Dead() { State = EPlayerState::DEAD; };
public:
};
