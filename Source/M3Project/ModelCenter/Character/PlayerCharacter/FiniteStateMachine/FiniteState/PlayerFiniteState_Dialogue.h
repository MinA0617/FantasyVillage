#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/PlayerCharacter/FiniteStateMachine/FiniteState/PlayerFiniteState.h"
#include "PlayerFiniteState_Dialogue.generated.h"

UCLASS()
class M3PROJECT_API UPlayerFiniteState_Dialogue : public UPlayerFiniteState
{
	GENERATED_BODY()
public:
	UPlayerFiniteState_Dialogue() { State = EPlayerState::DIALOGUE; }
public:
	void Init(APlayerCharacter* target) override;
	void Release() override;
	void MoveForward(float Value) override;
	void MoveRight(float Value) override {};
	void MouseLeftClick() override;
	void MouseWheel(float Value) override {};
	void JumpAction() override {};
	void Enter() override;
private:
    bool IsChanging;
};
