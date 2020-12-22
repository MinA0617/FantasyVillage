#include "PlayerFiniteState_React.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "ModelCenter/Character/AnimationManager.h"
#include "Components/CapsuleComponent.h"
#include "Base/M3GameInstance.h"

void UPlayerFiniteState_React::Init(APlayerCharacter* target)
{
	ReactCount = 1;
	bIsDown = false;
	Target = target;
	Target->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), 0.0f);
	Cast<UPlayerAnimInstance>(Target->GetAnimation())->bIsFullbody = true;
	UAnimMontage* ANI = UM3GameInstance::GetAnimationManager()->GetReactMontage(Target->CurrentWeaponType);
	Target->GetAnimation()->Montage_Play(ANI);
	Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UPlayerFiniteState_React::ReactEnd);
}

void UPlayerFiniteState_React::Release()
{
	Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
	ReactCount = 0;
	bIsDown = false;
	Cast<UPlayerAnimInstance>(Target->GetAnimation())->bIsFullbody = false;
	Target->GetCapsuleComponent()->SetSimulatePhysics(false);
}

void UPlayerFiniteState_React::React(ACharacter* Attacker)
{
	if (bIsDown == true) return;
	ReactCount++;
	if (ReactCount > 2)
	{
		UAnimMontage* ANI = UM3GameInstance::GetAnimationManager()->GetDownMontage(Target->CurrentWeaponType);
		Target->GetAnimation()->Montage_Stop(0.0f);
		Target->GetAnimation()->MontageInstances.Empty();
		Target->GetAnimation()->Montage_Play(ANI);

		FVector Force = Attacker->GetActorLocation() - Target->GetActorLocation();
		Force.Normalize();
		Force.Z += 0.3f;
		Force *= 2000.0f;
		Target->GetCapsuleComponent()->SetSimulatePhysics(true);
		Target->GetCapsuleComponent()->AddImpulse(Force, NAME_None, true);
		bIsDown = true;
	}
	else
	{
		UAnimMontage* ANI = UM3GameInstance::GetAnimationManager()->GetReactMontage(Target->CurrentWeaponType);
		Target->GetAnimation()->Montage_Stop(0.0f);
		Target->GetAnimation()->MontageInstances.Empty();
		Target->GetAnimation()->Montage_Play(ANI);
	}
}

void UPlayerFiniteState_React::ReactEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (Target->PlayerFiniteStateMachine->CurrentPlayerState != this) return;
	Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::BATTLE_START);
}