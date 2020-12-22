#include "MonsterFiniteState_Dead.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Character/AnimationManager.h"
#include "ModelCenter/Object/ItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "Base/M3GameInstance.h"
#include "GameHandler/QuestSystem/QuestSystem.h"

void UMonsterFiniteState_Dead::Init(AMonsterCharacter* target)
{
	Target = target;
	int SubIndex = (FMath::Rand() % Target->MonsterInfo.DeadAniCount) + 1;
	UAnimMontage* ANI = UM3GameInstance::GetAnimationManager()->GetMonsterDeadMontage(Target->MonsterInfo.ID, SubIndex);
	if (Target->GetMovementComponent()->IsFalling() == false)
	{
		Target->ApplyGravity(false);
	}
	Target->PlayAnimMontage(ANI);
	Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UMonsterFiniteState_Dead::DeadEnd);

	bAlphaBlend = false;
	BlendTime = 0.0f;

	for (int i = 0; i < Target->DropTable.Num(); i++)
	{
		if ((int)(Target->DropTable[i].Rate * 1000.0f) >= (FMath::Rand() % 1000))
		{
			AItemActor* ItemActor = Target->GetWorld()->SpawnActor<AItemActor>(AItemActor::StaticClass());
			ItemActor->TeleportTo(Target->GetActorLocation(), FRotator::ZeroRotator);
			ItemActor->BuildFromIndex(EItemType::RESOURCE, Target->DropTable[i].Index);
			FVector Force = Target->GetActorLocation() - UM3GameInstance::GetPC()->GetActorLocation();
			Force.Normalize();
			Force.Z += 0.1;
			Force *= 900.0f;
			ItemActor->ItemMesh->AddImpulse(Force, NAME_None, true);
		}
	}
	UM3GameInstance::GetQuestSystem()->KillMonster(Target->MonsterInfo.ID);
}

void UMonsterFiniteState_Dead::Release()
{
	Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
}

void UMonsterFiniteState_Dead::Tick(float DeltaTime)
{
	if (bAlphaBlend == true)
	{
		BlendTime += DeltaTime;
	}
	if (BlendTime > kBlendTime)
	{
		Target->Destroy();
	}
}

void UMonsterFiniteState_Dead::DeadEnd(UAnimMontage* Montage, bool bInterrupted)
{
	bAlphaBlend = true;
	Target->ApplyGravity(true);
}