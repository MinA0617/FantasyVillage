#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/Monster/MonsterFiniteStateMachine/FiniteState/MonsterFiniteState.h"
#include "MonsterFiniteState_Dead.generated.h"

const float kBlendTime = 3.0f;

UCLASS()
class M3PROJECT_API UMonsterFiniteState_Dead : public UMonsterFiniteState
{
	GENERATED_BODY()
public:
	UMonsterFiniteState_Dead() { State = EMonsterState::DEAD; };
public:
	virtual void Init(AMonsterCharacter* target);
	virtual void Release();
	virtual void Tick(float DeltaTime);
private:
	bool	bAlphaBlend;
	float	BlendTime;
	UFUNCTION() void DeadEnd(UAnimMontage* Montage, bool bInterrupted);
};
