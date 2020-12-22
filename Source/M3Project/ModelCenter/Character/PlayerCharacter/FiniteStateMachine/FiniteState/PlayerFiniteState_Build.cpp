#include "PlayerFiniteState_Build.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "ModelCenter/Map/MapManager.h"
#include "Base/M3GameInstance.h"
#include "GameHandler/M3GameMode.h"
#include "UI/UIMainWidget.h"
#include "ModelCenter/Character/AnimationManager.h"

void UPlayerFiniteState_Build::Init(APlayerCharacter* target)
{
	Target = target;

	if (UM3GameInstance::GetMapManager()->MapCreator->SetActivation(true) == false)
	{
		Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::RETURN_DEFUALT);
		return;
	}

	UClass* ABP = UM3GameInstance::GetAnimationManager()->GetBuildABP();
	Target->SetAnimation(ABP);
	bIsCreate = false;

	UAnimMontage* ChangeMontage = UM3GameInstance::GetAnimationManager()->GetBuildChangeMontage(true);
	Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
	Target->GetAnimation()->Montage_Play(ChangeMontage, 1.0f);
	Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UPlayerFiniteState_Build::ChangeEnd);


	IsChanging = true;
}

void UPlayerFiniteState_Build::Release()
{
	UM3GameInstance::GetMapManager()->MapCreator->SetActivation(false);
}

void UPlayerFiniteState_Build::MouseLeftClick()
{
	if (bIsCreate == false && IsChanging == false)
	{
		FVector Direction = UM3GameInstance::GetMapManager()->MapCreator->HelperActor->GetActorLocation() - Target->GetActorLocation();
		Direction.Z = 0.0f;
		Direction.Normalize();
		Target->SetActorRotation(Direction.Rotation());
		UAnimMontage* OneMontage = UM3GameInstance::GetAnimationManager()->GetBuildOneMontage();
		Target->GetAnimation()->OnMontageEnded.RemoveAll(this);
		Target->GetAnimation()->Montage_Play(OneMontage, 1.0f);
		Target->GetAnimation()->OnMontageEnded.AddDynamic(this, &UPlayerFiniteState_Build::CreateOneEnd);
		UAnimMontage* HelperMontage = UM3GameInstance::GetAnimationManager()->GetBuildHelperMontage();
		Target->HelperComponent.HelperMesh->PlayAnimation(HelperMontage, false);
		bIsCreate = true;
	}
}

void UPlayerFiniteState_Build::MouseRightClick()
{
	UUIMainWidget::GetInstance()->ShowItemListWheelWidget(EItemType::INSTALLATION);
	bIsPushRightClick = true;
}

void UPlayerFiniteState_Build::MouseRightRelease()
{
	UUIMainWidget::GetInstance()->ShowDefualtUI();
	bIsPushRightClick = false;
}

void UPlayerFiniteState_Build::MouseWheel(float Value)
{
	if (Value == 0.0f) return;
	if(bIsPushRightClick == false)
	{
		Target->MagnificationValue = Target->MagnificationValue - (Value * 50);
		if (Target->MagnificationValue < 200) Target->MagnificationValue = 200;
		if (Target->MagnificationValue > 800) Target->MagnificationValue = 800;
		Target->SpringArmComponent->TargetArmLength = Target->MagnificationValue;
	}
	else if(IsChanging == false)
	{
		if (Value > 0.01f)
		{
			if (UUIMainWidget::GetInstance()->ItemListWheelWidget->PrevIndex())
			UM3GameInstance::GetMapManager()->MapCreator->SetNextIndex(false);
		}
		else if (Value < -0.01f)
		{
			if (UUIMainWidget::GetInstance()->ItemListWheelWidget->NextIndex())
			UM3GameInstance::GetMapManager()->MapCreator->SetNextIndex(true);
		}
	}
}

void UPlayerFiniteState_Build::BuildOn()
{
	if (bIsCreate == false && IsChanging == false)
	{
		Target->PlayerFiniteStateMachine->StateEvent(EPlayerEvent::RETURN_DEFUALT);
	}
}

void UPlayerFiniteState_Build::CreateOneEnd(UAnimMontage* Montage, bool bInterrupted)
{
	UM3GameInstance::GetMapManager()->MapCreator->SetCubeMeshActivation(true);
	bIsCreate = false;
}

void UPlayerFiniteState_Build::ChangeEnd(UAnimMontage* Montage, bool bInterrupted)
{
	UM3GameInstance::GetMapManager()->MapCreator->SetCubeMeshActivation(true);
	IsChanging = false;
}

void UPlayerFiniteState_Build::NotifyStart()
{
	if (Target->PlayerFiniteStateMachine->CurrentPlayerState != this) return;
	if (UM3GameInstance::GetMapManager()->MapCreator->CreateCube())
	{
		UM3GameInstance::GetMapManager()->MapCreator->SetCubeMeshActivation(false);
	}
}
