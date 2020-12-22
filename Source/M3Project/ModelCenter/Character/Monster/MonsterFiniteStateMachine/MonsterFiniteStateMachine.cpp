#include "MonsterFiniteStateMachine.h"
#include "FiniteState/MonsterFiniteState_Attack.h"
#include "FiniteState/MonsterFiniteState_Expense.h"
#include "FiniteState/MonsterFiniteState_Trace.h"
#include "FiniteState/MonsterFiniteState_React.h"
#include "FiniteState/MonsterFiniteState_Dead.h"
#include "FiniteState/MonsterFiniteState_JumpingTrace.h"

UMonsterFiniteStateMachine::UMonsterFiniteStateMachine(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMonsterFiniteStateMachine::AddFiniteState(EMonsterState state, EMonsterEvent stateevent, EMonsterState nextstate)
{
	if (StateMachineList.Find(state) == nullptr)
	{
		StateMachineList.Add(state, TMap<EMonsterEvent, EMonsterState>());
	}
	StateMachineList[state].Add(stateevent, nextstate);
	if (MonsterFiniteStateList.Find(state) == nullptr)
	{
		UMonsterFiniteState* FS = nullptr;
		switch (state)
		{
		case EMonsterState::EXPENSE:
			FS = NewObject<UMonsterFiniteState_Expense>();
			break;
		case EMonsterState::TRACE:
			FS = NewObject<UMonsterFiniteState_Trace>();
			break;
		case EMonsterState::ATTACK:
			FS = NewObject<UMonsterFiniteState_Attack>();
			break;
		case EMonsterState::REACT:
			FS = NewObject<UMonsterFiniteState_React>();
			break;
		case EMonsterState::DEAD:
			FS = NewObject<UMonsterFiniteState_Dead>();
			break;
		case EMonsterState::JUMPING_TRACE:
			FS = NewObject<UMonsterFiniteState_JumpingTrace>();
			break;
		default:
			return;
		}
		MonsterFiniteStateList.Add(state, FS);
	}
}

void UMonsterFiniteStateMachine::StateEvent(EMonsterEvent Event)
{
	EMonsterState NextState = StateMachineList[CurrentPlayerState->State][Event];
	CurrentPlayerState->Release();
	CurrentPlayerState = MonsterFiniteStateList[NextState];
	CurrentPlayerState->Init(Owner);
}

void UMonsterFiniteStateMachine::SetStartState(EMonsterState StartState)
{
	CurrentPlayerState = MonsterFiniteStateList[StartState];
	CurrentPlayerState->Init(Owner);
}

void UMonsterFiniteStateMachine::Init(AMonsterCharacter* owner)
{
	Owner = owner;
}

void UMonsterFiniteStateMachine::Tick(float DeltaTime)
{
	if(CurrentPlayerState) CurrentPlayerState->Tick(DeltaTime);
}

void UMonsterFiniteStateMachine::ApplyDamage(int Damage, ACharacter* Attacker)
{
	if (CurrentPlayerState) CurrentPlayerState->ApplyDamage(Damage, Attacker);
}