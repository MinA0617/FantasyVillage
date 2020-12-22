#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/PlayerCharacter/FiniteStateMachine/FiniteState/PlayerFiniteState.h"
#include "PlayerFiniteState_Battle.generated.h"

UCLASS()
class M3PROJECT_API UPlayerFiniteState_Battle : public UPlayerFiniteState
{
	GENERATED_BODY()
public:
	UPlayerFiniteState_Battle() { State = EPlayerState::BATTLE; }
public:
	void Init(APlayerCharacter* target) override;
	void MouseLeftClick() override;
	void BattleOn() override;
	void Tick(float DeltaSecond);
public:
	UFUNCTION() void ChangeEnd(UAnimMontage* Montage, bool bInterrupted);
private:
	bool IsChanging;
	float ChangeTime;
};
