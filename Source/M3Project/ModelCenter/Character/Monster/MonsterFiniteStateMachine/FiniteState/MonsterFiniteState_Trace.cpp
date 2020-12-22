#include "MonsterFiniteState_Trace.h"
#include "ModelCenter/Map/NavigationSystem/M3NavigationSystem.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "Base/M3GameInstance.h"

void UMonsterFiniteState_Trace::Init(AMonsterCharacter* target)
{
	Target = target;
	RenewalTime = 999999.0f;
}

void UMonsterFiniteState_Trace::Release()
{
}

void UMonsterFiniteState_Trace::Tick(float DeltaTime)
{
	float TargetRange = (Target->GetActorLocation() - UM3GameInstance::GetPC()->GetActorLocation()).Size();
	if (TargetRange < Target->MonsterInfo.AttackRange)
	{
		Target->MonsterController->MonsterFiniteStateMachine->StateEvent(EMonsterEvent::ATTACK_RANGE_IN);
		return;
	}
	else if (TargetRange > kMaxLength)
	{
		Target->MonsterController->MonsterFiniteStateMachine->StateEvent(EMonsterEvent::MISSED_TARGET);
	}
	RenewalTime += DeltaTime;
	if (RenewalTime > kRenewalTime)
	{
		RenewalTime = 0;
		UM3NavigationSystem NavagationSystem;
		FVector StartPos = Target->GetActorLocation();
		FVector EndPos = UM3GameInstance::GetPC()->GetActorLocation();
		if (NavagationSystem.GetPath(Path, StartPos, EndPos) == false)
		{
			Target->MonsterController->MonsterFiniteStateMachine->StateEvent(EMonsterEvent::MISSED_TARGET);
		}
	}
	FVector TargetLocation = Target->GetActorLocation();
	FVector Goal = Path.GetHead()->GetValue();
	float Length = (TargetLocation - Goal).SizeSquared();
	if (Length < 30.0f)
	{
		Path.RemoveNode(Path.GetHead());
	}
	if (Path.Num() == 0)
	{
		Target->MonsterController->MonsterFiniteStateMachine->StateEvent(EMonsterEvent::MISSED_TARGET);
	}
	FVector Direction = Path.GetHead()->GetValue() - Target->GetActorLocation();
	Direction.Normalize();
	Target->AddMovementInput(Direction, 1.0f);
}