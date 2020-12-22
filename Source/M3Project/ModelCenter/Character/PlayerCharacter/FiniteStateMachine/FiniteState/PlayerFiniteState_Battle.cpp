#include "PlayerFiniteState_Battle.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "ModelCenter/Character/AnimationManager.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Object/ItemActor.h"
#include "Base/M3GameInstance.h"

const float kChangeTime = 5.0f;

void UPlayerFiniteState_Battle::Init(APlayerCharacter* target)
{
	Target = target;
	if (Target->CurrentWeaponType == EWeaponType::NONE)
	{
		Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::RETURN_DEFUALT);
		return;
	}
	UClass* ABP = UM3GameInstance::GetAnimationManager()->GetWeaponABP(Target->CurrentWeaponType);

	FNameEntryId OldID = Target->GetAnimation()->GetFName().GetComparisonIndex();
	FNameEntryId NewID = ABP->GetFName().GetComparisonIndex();

	IsChanging = false;
	if (OldID != NewID)
	{
		Target->SetAnimation(ABP);
		UAnimMontage* ChangeMontage = UM3GameInstance::GetAnimationManager()->GetWeaponChangeMontage(Target->CurrentWeaponType, true);
		Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
		Target->GetAnimation()->Montage_Play(ChangeMontage, 1.0f);
		Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UPlayerFiniteState_Battle::ChangeEnd);
		IsChanging = true;
	}
	ChangeTime = 0;
}

void UPlayerFiniteState_Battle::MouseLeftClick()
{
	if (IsChanging == false)
	{
		TArray<FHitResult> Result;
		if (UHelper::SphereCollision(Target, 150.0f, Result))
		{
			for (int i = 0; i < Result.Num(); i++)
			{
				AMonsterCharacter* Mop = Cast<AMonsterCharacter>(Result[i].Actor);
				if (Mop && Mop->IsDead() == false)
				{
					Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::ATTACK_START);
					return;
				}
			}
		}
		Result.Empty();
		if (UHelper::SphereCollision(Target, 150.0f, Result, ECC_GameTraceChannel1))
		{
			AItemActor* Item = nullptr;
			float MinLength = 10000000.0f;
			for (int i = 0; i < Result.Num(); i++)
			{
				float Length = (Target->GetActorLocation() - Result[i].Actor->GetActorLocation()).SizeSquared();
				AItemActor* ItemTemp = Cast<AItemActor>(Result[i].Actor);
				if (ItemTemp && MinLength > Length)
				{
					MinLength = Length;
					Item = ItemTemp;
				}
			}
			if (Item)
			{
				Item->GetItemToInventory();
				return;
			}
		}
		Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::ATTACK_START);
	}
}

void UPlayerFiniteState_Battle::BattleOn()
{
	if (IsChanging == false)
	{
		Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::RETURN_DEFUALT);
	}
}

void UPlayerFiniteState_Battle::ChangeEnd(UAnimMontage* Montage, bool bInterrupted)
{
	Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
	IsChanging = false;
}

void UPlayerFiniteState_Battle::Tick(float DeltaSecond)
{
	ChangeTime += DeltaSecond;
	if (ChangeTime > 5.0f)
	{
		if (IsChanging == false)
		{
			Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::RETURN_DEFUALT);
		}
	}
}