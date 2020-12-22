#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/Monster/MonsterFiniteStateMachine/FiniteState/MonsterFiniteState.h"
#include "MonsterFiniteState_JumpingTrace.generated.h"

UCLASS()
class M3PROJECT_API UMonsterFiniteState_JumpingTrace : public UMonsterFiniteState
{
	GENERATED_BODY()
public:
	UMonsterFiniteState_JumpingTrace() { State = EMonsterState::JUMPING_TRACE; };
public:
	void Init(AMonsterCharacter* target) override;
	void Release();
	UFUNCTION() void JumpEnd(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION() void NotifyStart();
private:
	void Jump();
	TDoubleLinkedList<FVector>	Path;
};
