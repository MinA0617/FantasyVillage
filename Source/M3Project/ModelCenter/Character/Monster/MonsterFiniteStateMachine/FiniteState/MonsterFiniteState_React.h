#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/Monster/MonsterFiniteStateMachine/FiniteState/MonsterFiniteState.h"
#include "MonsterFiniteState_React.generated.h"

const float kReactTime = 0.3f;

UCLASS()
class M3PROJECT_API UMonsterFiniteState_React : public UMonsterFiniteState
{
	GENERATED_BODY()
public:
	UMonsterFiniteState_React() { State = EMonsterState::REACT; };
public:
	virtual void Init(AMonsterCharacter* target);
	virtual void Release();
	UFUNCTION() void ReactEnd(UAnimMontage* Montage, bool bInterrupted);
};
