
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "MonsterController.h"
#include "Components/CapsuleComponent.h"
#include "Animation/MonsterAnimInstance.h"
#include "MonsterCharacter.generated.h"


USTRUCT(BlueprintType)
struct FMonsterDropTable
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() int Index;
	UPROPERTY() float Rate;
};


USTRUCT(BlueprintType)
struct FMonsterInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() int ID;
	UPROPERTY() FString Name;
	UPROPERTY() int MaxHP;
	UPROPERTY() int CurrentHP;
	UPROPERTY() float Speed;
	UPROPERTY() float AttackPoint;
	UPROPERTY() float AttackRange;
	UPROPERTY() int	DeadAniCount;
	UPROPERTY() int	ReactAniCount;
};

UCLASS()
class M3PROJECT_API AMonsterCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AMonsterCharacter(const FObjectInitializer& ObjectInitializer);
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void PossessedBy(AController* NewController) override;
public:
	FMonsterInfo MonsterInfo;
	TArray<FMonsterDropTable> DropTable;
	UPROPERTY() USkeletalMeshComponent* BodyMesh;
	UPROPERTY() AMonsterController* MonsterController;
	UPROPERTY() UCapsuleComponent* WeaponCapsuleComponent;
public:
	void ApplyDamage(int Damage, ACharacter* Attacker);
	void BuildMonster(FMonsterTableResource* Data);
	void SetAnimation(int MonsterID);
	void ApplyGravity(bool is_ture);
	UMonsterAnimInstance* GetAnimation();
	bool IsDead();
private:
	void BuildFSM(EMonsterState Start, FString& Data);
};

USTRUCT(BlueprintType)
struct FMonsterTableResource : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FString			Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) int				MaxHP;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float			Speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float			AttackPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float			AttackRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) int32			MeshResource;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float			CapsuleHalfheight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float			CapsuleRadius;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) int				DeadAniCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) int				ReactAniCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) EMonsterState	FSMStart;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FString			FSMList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FString			DropList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float			WeaponCapsuleHalfheight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float			WeaponCapsuleRadius;
};