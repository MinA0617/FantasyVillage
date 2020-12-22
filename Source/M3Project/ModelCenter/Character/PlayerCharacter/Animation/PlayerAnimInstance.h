#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class APlayerCharacter;

UCLASS()
class M3PROJECT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPlayerAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true)) float OwnerSpeed;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true)) bool IsFalling;
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly) bool bIsFullbody;
private:
	UFUNCTION()	void AnimNotify_AttackStart();
	UFUNCTION() void AnimNotify_AttackEnd();
	UFUNCTION() void AnimNotify_ChangeStart();
	UFUNCTION() void AnimNotify_ChangeEnd();
	UFUNCTION() void AnimNotify_CreateStart();
public:
	APlayerCharacter* OwnerCharacter;
};
