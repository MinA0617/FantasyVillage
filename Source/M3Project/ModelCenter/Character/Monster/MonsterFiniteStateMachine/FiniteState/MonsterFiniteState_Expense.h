// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/Monster/MonsterFiniteStateMachine/FiniteState/MonsterFiniteState.h"
#include "MonsterFiniteState_Expense.generated.h"

UCLASS()
class M3PROJECT_API UMonsterFiniteState_Expense : public UMonsterFiniteState
{
	GENERATED_BODY()
public:
	UMonsterFiniteState_Expense() { State = EMonsterState::EXPENSE; };
public:
	void Init(AMonsterCharacter* target) override;
	void Release();
	void Tick(float DeltaTime) override;
};
