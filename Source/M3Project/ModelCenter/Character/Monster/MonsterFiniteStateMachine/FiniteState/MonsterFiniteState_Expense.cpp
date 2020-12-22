#include "MonsterFiniteState_Expense.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "Base/M3GameInstance.h"

const float kTraceOnLength = 1500.0f;

void UMonsterFiniteState_Expense::Init(AMonsterCharacter* target)
{
	Target = target;
}

void UMonsterFiniteState_Expense::Release()
{

}

void UMonsterFiniteState_Expense::Tick(float DeltaTime)
{
	float TargetRange = (Target->GetActorLocation() - UM3GameInstance::GetPC()->GetActorLocation()).Size();
	if (TargetRange < kTraceOnLength)
	{
		Target->MonsterController->MonsterFiniteStateMachine->StateEvent(EMonsterEvent::DISCOVERY_TARGET);
		return;
	}
}