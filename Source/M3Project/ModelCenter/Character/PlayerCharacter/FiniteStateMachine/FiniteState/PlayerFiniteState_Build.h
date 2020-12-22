#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/PlayerCharacter/FiniteStateMachine/FiniteState/PlayerFiniteState.h"
#include "GameFramework/Character.h"
#include "PlayerFiniteState_Build.generated.h"

UCLASS()
class M3PROJECT_API UPlayerFiniteState_Build : public UPlayerFiniteState
{
	GENERATED_BODY()
public:
	UPlayerFiniteState_Build() { State = EPlayerState::BUILD; }
public:
	void Init(APlayerCharacter* target) override;
	void Release() override;
	void MouseLeftClick() override;
	void MouseRightClick() override;
	void MouseRightRelease() override;
	void MouseWheel(float Value) override;
	void BuildOn() override;
public:
	void NotifyStart();
	UFUNCTION() void CreateOneEnd(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION() void ChangeEnd(UAnimMontage* Montage, bool bInterrupted);
private:
	bool IsChanging;
	bool bIsCreate;
	bool bIsPushRightClick;
};
