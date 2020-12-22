#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/Monster/MonsterFiniteStateMachine/FiniteState/MonsterFiniteState.h"
#include "MonsterFiniteState_Trace.generated.h"

const float kRenewalTime = 0.2f;

UCLASS()
class M3PROJECT_API UMonsterFiniteState_Trace : public UMonsterFiniteState
{
	GENERATED_BODY()
public:
	UMonsterFiniteState_Trace() { State = EMonsterState::TRACE; };
public:
	void Init(AMonsterCharacter* target) override;
	void Tick(float DeltaTime) override;
	void Release();
private:
    float						RenewalTime;
	TDoubleLinkedList<FVector>	Path;
};
