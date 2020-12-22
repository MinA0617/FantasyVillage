#include "PlayerAnimInstance.h"
#include "ConstructorHelpers.h"
#include "../FiniteStateMachine/FiniteState/PlayerFiniteState_Attack.h"
#include "../FiniteStateMachine/FiniteState/PlayerFiniteState_Build.h"
#include "../PlayerCharacter.h"
#include "../../Base/CostomizeCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	OwnerSpeed = 0.0f;
	IsFalling = false;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerCharacter)
	{
		OwnerSpeed = OwnerCharacter->GetVelocity().Size();
		IsFalling = OwnerCharacter->GetMovementComponent()->IsFalling();
	}
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::AnimNotify_AttackStart()
{
	if (OwnerCharacter)
	{
		UPlayerFiniteState_Attack* AttackState = Cast<UPlayerFiniteState_Attack>(OwnerCharacter->PlayerFiniteStateMachine->CurrentPlayerState);
		if (AttackState)
		{
			AttackState->NotifyStart();
		}
	}
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	if (OwnerCharacter)
	{
		UPlayerFiniteState_Attack* AttackState = Cast<UPlayerFiniteState_Attack>(OwnerCharacter->PlayerFiniteStateMachine->CurrentPlayerState);
		if (AttackState)
		{
			AttackState->NotifyEnd();
		}
	}
}

void UPlayerAnimInstance::AnimNotify_ChangeStart()
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(OwnerCharacter);
	if (PC)
	{
		PC->ChangeBattleMode(true);
	}
}

void UPlayerAnimInstance::AnimNotify_ChangeEnd()
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(OwnerCharacter);
	if (PC)
	{
		PC->ChangeBattleMode(false);
	}
}

void UPlayerAnimInstance::AnimNotify_CreateStart()
{
	if (OwnerCharacter)
	{
		UPlayerFiniteState_Build* BuildState = Cast<UPlayerFiniteState_Build>(OwnerCharacter->PlayerFiniteStateMachine->CurrentPlayerState);
		if (BuildState)
		{
			BuildState->NotifyStart();
		}
	}
}