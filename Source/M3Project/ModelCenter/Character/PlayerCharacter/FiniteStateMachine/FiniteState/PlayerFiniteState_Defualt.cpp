#include "PlayerFiniteState_Defualt.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "ModelCenter/Character/NonPlayerCharacter/NonPlayerCharacter.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Character/AnimationManager.h"
#include "ModelCenter/Object/ItemActor.h"

void UPlayerFiniteState_Defualt::Init(APlayerCharacter* target)
{
	Target = target;
	IsChanging = false;

	UClass* ABP = UM3GameInstance::GetAnimationManager()->GetWeaponABP(EWeaponType::NONE);

	if (Target->GetAnimation()->GetClass() == UM3GameInstance::GetAnimationManager()->GetBuildABP())
	{
		Target->SetAnimation(ABP);
		UAnimMontage* ChangeMontage = UM3GameInstance::GetAnimationManager()->GetBuildChangeMontage(false);
		if (ChangeMontage)
		{
			Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
			Target->GetAnimation()->Montage_Play(ChangeMontage, 1.0f);
			Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UPlayerFiniteState_Defualt::ChangeEnd);
			IsChanging = true;
		}
	}
	else if(Target->GetAnimation()->GetClass() == UM3GameInstance::GetAnimationManager()->GetWeaponABP(Target->CurrentWeaponType))
	{
		Target->SetAnimation(ABP);
		UAnimMontage* ChangeMontage = UM3GameInstance::GetAnimationManager()->GetWeaponChangeMontage(Target->CurrentWeaponType, false);
		if (ChangeMontage)
		{
			Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
			Target->GetAnimation()->Montage_Play(ChangeMontage, 1.0f);
			Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UPlayerFiniteState_Defualt::ChangeEnd);
			IsChanging = true;
		}
	}
	else
	{
		Target->SetAnimation(ABP);
	}
}

void UPlayerFiniteState_Defualt::MouseLeftClick()
{
	TArray<FHitResult> Result;
	if (UHelper::SphereCollision(Target, 150.0f, Result))
	{
		for (int i = 0; i < Result.Num(); i++)
		{
			AMonsterCharacter* Mop = Cast<AMonsterCharacter>(Result[i].Actor);
			if (Mop && Mop->IsDead() == false)
			{
				BattleOn();
				return;
			}
		}
	}
	Result.Empty();
	if (UHelper::SphereCollision(Target, 150.0f, Result, ECC_GameTraceChannel1))
	{
		AItemActor* Item = nullptr;
		float MinLength = 10000.0f;
		for (int i = 0; i < Result.Num(); i++)
		{
			float Length = (Target->GetActorLocation() - Result[i].Actor->GetActorLocation()).SizeSquared();
			AItemActor* ItemTemp = Cast<AItemActor>(Result[i].Actor);
			if (MinLength > Length)
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
	Result.Empty();
	if (UHelper::SphereCollision(Target, 300.0f, Result))
	{
		for (int i = 0; i < Result.Num(); i++)
		{
			ANonPlayerCharacter* NPC = Cast<ANonPlayerCharacter>(Result[i].Actor);
			if (NPC)
			{
				Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::DIALOGUE_START);
				NPC->Converse();
				return;
			}
		}
	}
	BattleOn();
}

void UPlayerFiniteState_Defualt::BattleOn()
{
	if (IsChanging == false)
	{
		Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::BATTLE_START);
	}
}

void UPlayerFiniteState_Defualt::BuildOn()
{
	if (IsChanging == false)
	{
		Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::BUILD_START);
	}
}

void UPlayerFiniteState_Defualt::ChangeEnd(UAnimMontage* Montage, bool bInterrupted)
{
	Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
	IsChanging = false;
}