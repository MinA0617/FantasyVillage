#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/PlayerCharacter/FiniteStateMachine/FiniteState/PlayerFiniteState.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"
#include "ModelCenter/Object/InstancedActor.h"
#include "PlayerFiniteState_Attack.generated.h"

UCLASS()
class M3PROJECT_API UPlayerFiniteState_Attack : public UPlayerFiniteState
{
	GENERATED_BODY()
public:
	UPlayerFiniteState_Attack() { State = EPlayerState::ATTACK; };
public:
	void Init(APlayerCharacter* target) override;
	void Release() override;
	void MouseLeftClick() override;
public:
	UFUNCTION()	void NotifyStart();
	UFUNCTION() void NotifyEnd();
	UFUNCTION() void AttackEnd(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	int Combo;
	int ComboCount;
	bool IsSlash;
	bool IsNextCombo;
	TArray<AMonsterCharacter*> AttackOverlapList;
	TArray<FVector> CubeOverlapList;
};
