#include "MonsterFiniteState_Attack.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Character/AnimationManager.h"
#include "Components/CapsuleComponent.h"
#include "Base/M3GameInstance.h"

void UMonsterFiniteState_Attack::Init(AMonsterCharacter* target)
{
	Target = target;

	FVector Direction = UM3GameInstance::GetPC()->GetActorLocation() - Target->GetActorLocation();
	Direction.Z = 0.0f;
	Direction.Normalize();
	Target->SetActorRotation(Direction.Rotation());

	UAnimMontage* ANI = UM3GameInstance::GetAnimationManager()->GetMonsterAttackMontage(Target->MonsterInfo.ID);
	if (Target->GetMovementComponent()->IsFalling() == false)
	{
		Target->ApplyGravity(false);
	}
	Target->GetAnimation()->MontageInstances.Empty();
	Target->PlayAnimMontage(ANI);
	Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UMonsterFiniteState_Attack::AttackEnd);
}

void UMonsterFiniteState_Attack::Release()
{
	Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
	Target->WeaponCapsuleComponent->OnComponentBeginOverlap.Clear();
	Target->ApplyGravity(true);
}

void UMonsterFiniteState_Attack::NotifyStart()
{
	if (Target->MonsterController->MonsterFiniteStateMachine->CurrentPlayerState != this) return;
	Target->WeaponCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &UMonsterFiniteState_Attack::OnOverlapBegin);
	AttackOverlapList.Empty();
}

void UMonsterFiniteState_Attack::NotifyEnd()
{
	if (Target->MonsterController->MonsterFiniteStateMachine->CurrentPlayerState != this) return;
	Target->WeaponCapsuleComponent->OnComponentBeginOverlap.Clear();
	for (APlayerCharacter* FlagCharacter : AttackOverlapList)
	{
		FlagCharacter->ApplyDamage(Target->MonsterInfo.AttackPoint, Target);
	}
	AttackOverlapList.Empty();
}

void UMonsterFiniteState_Attack::AttackEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (Target->MonsterController->MonsterFiniteStateMachine->CurrentPlayerState != this) return;
	Target->MonsterController->MonsterFiniteStateMachine->StateEvent(EMonsterEvent::DISCOVERY_TARGET);
}

void UMonsterFiniteState_Attack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		for (APlayerCharacter* FlagCharacter : AttackOverlapList)
		{
			if (FlagCharacter == Player)	return;
		}
		AttackOverlapList.Add(Player);
	}
}



