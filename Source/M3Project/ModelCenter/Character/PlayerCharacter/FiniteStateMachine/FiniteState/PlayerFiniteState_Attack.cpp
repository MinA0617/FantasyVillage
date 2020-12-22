#include "PlayerFiniteState_Attack.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "ModelCenter/Character/AnimationManager.h"
#include "Components/CapsuleComponent.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Object/ItemActor.h"
#include "ModelCenter/Map/MapManager.h"
#include "Base/M3GameInstance.h"
#include "Base/Helper.h"

const int kTwoHandedMaxCombo = 2;

void UPlayerFiniteState_Attack::Init(APlayerCharacter* target)
{
	Target = target;
	IsSlash = false;
	IsNextCombo = false;
	Combo = 1;
	ComboCount = 1;
	if (Target->CurrentWeaponType == EWeaponType::NONE)
	{
		Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::RETURN_DEFUALT);
		return;
	}
	UAnimMontage* ANI = UM3GameInstance::GetAnimationManager()->GetWeaponAttackMontage(Target->CurrentWeaponType, Combo);
	Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
	Target->GetAnimation()->MontageInstances.Empty();
	Target->GetAnimation()->Montage_Play(ANI);
	Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UPlayerFiniteState_Attack::AttackEnd);
}

void UPlayerFiniteState_Attack::Release()
{
	Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
	Target->SlashWeaponCollisonComponent->OnComponentBeginOverlap.Clear();
}

void UPlayerFiniteState_Attack::MouseLeftClick()
{
	if (IsSlash == true)
	{
		IsNextCombo = true;
	}
}

void UPlayerFiniteState_Attack::NotifyStart()
{
	if (Target->PlayerFiniteStateMachine->CurrentPlayerState != this) return;
	IsSlash = true;
	Target->SlashWeaponCollisonComponent->OnComponentBeginOverlap.AddDynamic(this, &UPlayerFiniteState_Attack::OnOverlapBegin);
}

void UPlayerFiniteState_Attack::NotifyEnd()
{
	if (Target->PlayerFiniteStateMachine->CurrentPlayerState != this) return;
	IsSlash = false;
	if (IsNextCombo == true && kTwoHandedMaxCombo > Combo)
	{
		IsNextCombo = false;
		Combo++;
		if (Target->CurrentWeaponType == EWeaponType::NONE)
		{
			Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::RETURN_DEFUALT);
			return;
		}
		UAnimMontage* ANI = UM3GameInstance::GetAnimationManager()->GetWeaponAttackMontage(Target->CurrentWeaponType, Combo);
		ComboCount++;
		Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
		Target->GetAnimation()->Montage_Play(ANI);
		Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UPlayerFiniteState_Attack::AttackEnd);
	}
	Target->SlashWeaponCollisonComponent->OnComponentBeginOverlap.Clear();
	for (AMonsterCharacter* FlagMonster : AttackOverlapList)
	{
		FlagMonster->ApplyDamage(Target->GetPlayerInfo().AttackPoint, Target);
	}
	AttackOverlapList.Empty();

	for (FVector& FlagPosition : CubeOverlapList)
	{
		UM3GameInstance::GetMapManager()->DemageCube(FlagPosition, Target->GetPlayerInfo().AttackPoint);
	}
	CubeOverlapList.Empty();
}

void UPlayerFiniteState_Attack::AttackEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (Target->PlayerFiniteStateMachine->CurrentPlayerState != this) return;
	ComboCount--;
	if (ComboCount == 0)
	{
		Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::BATTLE_START);
	}
}

void UPlayerFiniteState_Attack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Target->PlayerFiniteStateMachine->CurrentPlayerState != this) return;
	AMonsterCharacter* Monster = Cast<AMonsterCharacter>(OtherActor);
	if (Monster)
	{
		for (AMonsterCharacter* FlagMonster : AttackOverlapList)
		{
			if (FlagMonster == Monster)	return;
		}
		AttackOverlapList.Add(Monster);
	}
	AInstancedActor* Cube = Cast<AInstancedActor>(OtherActor);
	if (Cube)
	{
		if (Cube->Durability == 0) return;
		const float& Length = Target->EquipmentItem.WeaponItem->DefaultInfo.WeaponLenght;
		const FVector Start = OverlappedComp->GetComponentTransform().TransformPosition(FVector(0.f, .0f, -Length));
		const FVector End = OverlappedComp->GetComponentTransform().TransformPosition(FVector(0.f, .0f, -Length * 3));

		TSet<int32> SetList;
		for (int i = 0; i < 9; i++)
		{
			TArray<int32> List = Cube->InstancedMesh->GetInstancesOverlappingSphere(Start + ((Start - End) * 0.125f * i), Length * 0.2f);
			if (UE_EDITOR)
			{
				UHelper::DrawSphere(Target->GetWorld(), Start + ((Start - End) * 0.125f * i), FColor(255.0f - (0.125f * i * 255), 255.0f - (0.125f * i * 255), 255.0f - (0.125f * i * 255), 1.0f), Length * 0.2f, 1.0f);
			}
			for (int j = 0; j < List.Num(); j++)
			{
				if (SetList.Find(List[j]) == nullptr)
				{
					SetList.Add(List[j]);
				}
			}
		}
		for (int32 Temp : SetList)
		{
			FTransform Transform = FTransform();
			Cube->InstancedMesh->GetInstanceTransform(Temp, Transform);
			const FVector InstancePos = Transform.GetLocation();
			for (FVector& FlagPosition : CubeOverlapList)
			{
				if (FlagPosition.Equals(InstancePos, 1.0f)) break;
			}
			CubeOverlapList.Add(InstancePos);
		}
	}
}