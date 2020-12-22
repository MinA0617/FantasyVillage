#include "MonsterAnimInstance.h"
#include "../MonsterCharacter.h"
#include "../MonsterFiniteStateMachine/FiniteState/MonsterFiniteState_Attack.h"
#include "../MonsterFiniteStateMachine/FiniteState/MonsterFiniteState_JumpingTrace.h"

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerCharacter)
	{
		OwnerSpeed = OwnerCharacter->GetVelocity().Size();
		IsFalling = OwnerCharacter->GetMovementComponent()->IsFalling();
	}
}

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<AMonsterCharacter>(TryGetPawnOwner());
}

void UMonsterAnimInstance::AnimNotify_AttackStart()
{
	if (OwnerCharacter)
	{
		UMonsterFiniteState_Attack* AttackState = Cast<UMonsterFiniteState_Attack>(OwnerCharacter->MonsterController->MonsterFiniteStateMachine->CurrentPlayerState);
		if (AttackState)
		{
			AttackState->NotifyStart();
		}
	}
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	if (OwnerCharacter)
	{
		UMonsterFiniteState_Attack* AttackState = Cast<UMonsterFiniteState_Attack>(OwnerCharacter->MonsterController->MonsterFiniteStateMachine->CurrentPlayerState);
		if (AttackState)
		{
			AttackState->NotifyEnd();
		}
	}
}

void UMonsterAnimInstance::AnimNotify_JumpStart()
{
	if (OwnerCharacter)
	{
		UMonsterFiniteState_JumpingTrace* JumpingTraceState = Cast<UMonsterFiniteState_JumpingTrace>(OwnerCharacter->MonsterController->MonsterFiniteStateMachine->CurrentPlayerState);
		if (JumpingTraceState)
		{
			JumpingTraceState->NotifyStart();
		}
	}
}