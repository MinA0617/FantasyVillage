#include "MonsterFiniteState_React.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Character/AnimationManager.h"
#include "Base/M3GameInstance.h"
#include "GameHandler/M3GameMode.h"
#include "TimerManager.h"

void UMonsterFiniteState_React::Init(AMonsterCharacter* target)
{
	Target = target;
	int SubIndex = (FMath::Rand() % Target->MonsterInfo.ReactAniCount) + 1;
	UAnimMontage* ANI = UM3GameInstance::GetAnimationManager()->GetMonsterReactMontage(Target->MonsterInfo.ID, SubIndex);
	Target->GetAnimation()->MontageInstances.Empty();
	Target->PlayAnimMontage(ANI);
	Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UMonsterFiniteState_React::ReactEnd);
}

void UMonsterFiniteState_React::Release()
{
	Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
}

void UMonsterFiniteState_React::ReactEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (Target->MonsterController->MonsterFiniteStateMachine->CurrentPlayerState != this) return;
	Target->MonsterController->MonsterFiniteStateMachine->StateEvent(EMonsterEvent::DISCOVERY_TARGET);
}