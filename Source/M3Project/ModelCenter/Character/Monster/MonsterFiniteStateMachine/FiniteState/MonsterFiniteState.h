// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/NoExportTypes.h"
#include "MonsterFiniteState.generated.h"

const float kMaxLength = 5000.0f;

class AMonsterCharacter;

UENUM()
enum class EMonsterState : uint8
{
	EXPENSE,
	TRACE,
	ATTACK,
	REACT,
	DEAD,
	JUMPING_TRACE,
	__MAX__,
};

UENUM()
enum class EMonsterEvent : uint8
{
	DISCOVERY_TARGET,
	MISSED_TARGET,
	ATTACK_RANGE_IN,
	REACT,
	DEAD,
};

UCLASS()
class M3PROJECT_API UMonsterFiniteState : public UObject
{
	GENERATED_BODY()
public:
	EMonsterState State;
	AMonsterCharacter* Target;
	virtual void Init(AMonsterCharacter* target) { Target = target; };
	virtual void Tick(float DeltaTime) {};
	virtual void ApplyDamage(int Damage, ACharacter* Attacker);
	virtual void Release() {};
};
