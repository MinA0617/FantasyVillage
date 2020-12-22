// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

class AMonsterCharacter;

UCLASS()
class M3PROJECT_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true)) float OwnerSpeed;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true)) bool IsFalling;
public:
	UFUNCTION()	void AnimNotify_AttackStart();
	UFUNCTION() void AnimNotify_AttackEnd();
	UFUNCTION() void AnimNotify_JumpStart();
public:
	AMonsterCharacter* OwnerCharacter;
};
