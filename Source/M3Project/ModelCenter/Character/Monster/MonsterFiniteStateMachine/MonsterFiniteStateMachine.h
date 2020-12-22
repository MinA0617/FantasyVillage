#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FiniteState/MonsterFiniteState.h"
#include "MonsterFiniteStateMachine.generated.h"

UCLASS()
class M3PROJECT_API UMonsterFiniteStateMachine : public UObject
{
	GENERATED_BODY()
public:
	UMonsterFiniteStateMachine(const FObjectInitializer& ObjectInitializer);
public:
	UMonsterFiniteState* CurrentPlayerState;
private:
	TMap<EMonsterState, TMap<EMonsterEvent, EMonsterState>> StateMachineList;
	UPROPERTY() TMap<EMonsterState, UMonsterFiniteState*> MonsterFiniteStateList;
	AMonsterCharacter* Owner;
public:
	void AddFiniteState(EMonsterState state, EMonsterEvent stateevent, EMonsterState nextstate);
	void StateEvent(EMonsterEvent Event);
	void SetStartState(EMonsterState StartState);
public:
	void Init(AMonsterCharacter* owner);
	void Tick(float DeltaTime);
	void ApplyDamage(int Damage, ACharacter* Attacker);
};