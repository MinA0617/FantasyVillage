#include "PlayerFiniteState.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "GameHandler/QuestSystem/QuestSystem.h"
#include "Base/M3GameInstance.h"

void UPlayerFiniteState::MoveForward(float Value)
{
	if (Target && Target->Controller && (Value != 0.0f))
	{
		const FRotator Rotation = Target->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		Target->AddMovementInput(Direction, Value);
		UM3GameInstance::GetQuestSystem()->PositionCheck(Target->GetActorLocation());
	}
}

void UPlayerFiniteState::MoveRight(float Value)
{
	if (Target && Target->Controller && (Value != 0.0f))
	{
		const FRotator Rotation = Target->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		Target->AddMovementInput(Direction, Value);
		UM3GameInstance::GetQuestSystem()->PositionCheck(Target->GetActorLocation());
	}
}

void UPlayerFiniteState::MouseWheel(float Value)
{
	if (Target)
	{
		Target->MagnificationValue = Target->MagnificationValue - (Value * 50);
		if (Target->MagnificationValue < 200) Target->MagnificationValue = 200;
		if (Target->MagnificationValue > 800) Target->MagnificationValue = 800;
		Target->SpringArmComponent->TargetArmLength = Target->MagnificationValue;
	}
}

void UPlayerFiniteState::JumpAction()
{
	if (Target)
	{
		Target->Jump();
	}
}
