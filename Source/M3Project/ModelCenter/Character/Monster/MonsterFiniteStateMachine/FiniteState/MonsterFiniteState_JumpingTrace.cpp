#include "MonsterFiniteState_JumpingTrace.h"
#include "MonsterFiniteState_Trace.h"
#include "ModelCenter/Map/NavigationSystem/M3NavigationSystem.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Character/AnimationManager.h"
#include "Base/M3GameInstance.h"

void UMonsterFiniteState_JumpingTrace::Init(AMonsterCharacter* target)
{
	Target = target;
	Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UMonsterFiniteState_JumpingTrace::JumpEnd);
	Jump();
}

void UMonsterFiniteState_JumpingTrace::Release()
{
	Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
}

void UMonsterFiniteState_JumpingTrace::JumpEnd(UAnimMontage* Montage, bool bInterrupted)
{
	Jump();
}

void UMonsterFiniteState_JumpingTrace::NotifyStart()
{
	Target->Jump();
}

void UMonsterFiniteState_JumpingTrace::Jump()
{
	if (Target->MonsterController->MonsterFiniteStateMachine->CurrentPlayerState != this) return;
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
	UM3NavigationSystem NavagationSystem;
	FVector StartPos = Target->GetActorLocation();
	FVector EndPos = UM3GameInstance::GetPC()->GetActorLocation();
	if (NavagationSystem.GetPath(Path, StartPos, EndPos) == false)
	{
		Target->MonsterController->MonsterFiniteStateMachine->StateEvent(EMonsterEvent::MISSED_TARGET);
		return;
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
	Direction.Z = 0.0f;
	Direction.Normalize();
	Target->SetActorRotation(Direction.Rotation());
	UAnimMontage* ANI = UM3GameInstance::GetAnimationManager()->GetMonsterRunMontage(Target->MonsterInfo.ID);
	Target->GetAnimation()->MontageInstances.Empty();
	Target->PlayAnimMontage(ANI);
}