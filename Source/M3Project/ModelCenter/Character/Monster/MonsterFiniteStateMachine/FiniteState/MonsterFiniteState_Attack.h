#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/Monster/MonsterFiniteStateMachine/FiniteState/MonsterFiniteState.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "MonsterFiniteState_Attack.generated.h"

UCLASS()
class M3PROJECT_API UMonsterFiniteState_Attack : public UMonsterFiniteState
{
	GENERATED_BODY()
public:
	UMonsterFiniteState_Attack() { State = EMonsterState::ATTACK; };
public:
    virtual void Init(AMonsterCharacter* target);
    virtual void Release();
	UFUNCTION()	void NotifyStart();
	UFUNCTION() void NotifyEnd();
public:
	UFUNCTION() void AttackEnd(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	TArray<APlayerCharacter*> AttackOverlapList;
};
