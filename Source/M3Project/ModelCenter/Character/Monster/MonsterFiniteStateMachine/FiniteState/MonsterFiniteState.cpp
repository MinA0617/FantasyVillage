#include "MonsterFiniteState.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"

void UMonsterFiniteState::ApplyDamage(int Damage, ACharacter * Attacker)
{
	Target->MonsterInfo.CurrentHP -= Damage;
	if (Target->MonsterInfo.CurrentHP <= 0)
	{
		if (State != EMonsterState::DEAD)
		{
			Target->MonsterController->MonsterFiniteStateMachine->StateEvent(EMonsterEvent::DEAD);
		}
	}
	else
	{
		if (State != EMonsterState::REACT)
		{
			Target->MonsterController->MonsterFiniteStateMachine->StateEvent(EMonsterEvent::REACT);
		}
	}
}
