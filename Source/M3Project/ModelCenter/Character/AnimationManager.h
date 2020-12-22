#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerCharacter/PlayerCharacter.h"
#include "AnimationManager.generated.h"

USTRUCT(BlueprintType)
struct FAnimationResourceTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Resource;

};

UCLASS()
class M3PROJECT_API UAnimationManager : public UObject
{
	GENERATED_BODY()
public:
	UAnimationManager(const FObjectInitializer& ObjectInitializer);
public:
	UClass*							GetWeaponABP(EWeaponType type);
	UClass*							GetMonsterABP(int index);
	UClass*							GetBuildABP();
	UAnimMontage*					GetReactMontage(EWeaponType type);
	UAnimMontage*					GetDownMontage(EWeaponType type);
	UAnimMontage*					GetWeaponAttackMontage(EWeaponType type, int Combo);
	UAnimMontage*					GetWeaponChangeMontage(EWeaponType type, bool IsIn);
	UAnimMontage*					GetMonsterAttackMontage(int MonsterIndex);
	UAnimMontage*					GetMonsterRunMontage(int MonsterIndex);
	UAnimMontage*					GetMonsterReactMontage(int MonsterIndex, int SubIndex);
	UAnimMontage*					GetMonsterDeadMontage(int MonsterIndex, int SubIndex);
	UAnimMontage*					GetBuildChangeMontage(bool IsIn);
	UAnimMontage*					GetBuildOneMontage();
	UAnimMontage*					GetBuildReactMontage();
	UAnimMontage*					GetBuildDownMontage();
	UAnimMontage*					GetBuildHelperMontage();
private:
	TMap<FString, UClass*>			AnimationList;
	TMap<FString, UAnimMontage*>	AnimMontageList;
};
