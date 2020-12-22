#include "MonsterCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "MonsterController.h"
#include "Base/M3GameInstance.h"
#include "Resource/M3ResourceManager.h"
#include "Engine/SkeletalMesh.h"
#include "Components/CapsuleComponent.h"
#include "Animation/MonsterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ModelCenter/Character/AnimationManager.h"
#include "LogicObject/Item/ItemManager.h"
#include "ConstructorHelpers.h"

AMonsterCharacter::AMonsterCharacter(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponCapsuleComponent = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("WeaponCapsuleComponent"));
	BodyMesh = GetMesh();
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BodyMesh->SetRelativeRotation(FRotator(0, -90, 0));
	AIControllerClass = AMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	FName SocketWeapon("SocketWeapon");
	WeaponCapsuleComponent->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, SocketWeapon);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1000.0f, 0.0f);

	if (UE_EDITOR)
	{
		GetCapsuleComponent()->bHiddenInGame = false;
		WeaponCapsuleComponent->bHiddenInGame = false;
	}
	FBodyInstance* RootBI = GetCapsuleComponent()->GetBodyInstance(NAME_None, false);
	RootBI->bLockXRotation = true;
	RootBI->bLockYRotation = true;


}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AMonsterController* MC = Cast<AMonsterController>(NewController);
	if (MC) MC->MonsterFiniteStateMachine->Init(this);
	MC->HomeLocation = GetActorLocation();
	MonsterController = MC;
}

void AMonsterCharacter::ApplyDamage(int Damage, ACharacter* Attacker)
{
	MonsterController->MonsterFiniteStateMachine->ApplyDamage(Damage, Attacker);
}

void AMonsterCharacter::BuildMonster(FMonsterTableResource* Data)
{
	MonsterInfo.Name = Data->Name;
	MonsterInfo.MaxHP = Data->MaxHP;
	MonsterInfo.CurrentHP = Data->MaxHP;
	MonsterInfo.Speed = Data->Speed;
	MonsterInfo.AttackPoint = Data->AttackPoint;
	MonsterInfo.AttackRange = Data->AttackRange;
	MonsterInfo.DeadAniCount = Data->DeadAniCount;
	MonsterInfo.ReactAniCount = Data->ReactAniCount;
	
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.Speed;
	GetCharacterMovement()->JumpZVelocity = 250.0f;
	GetCapsuleComponent()->SetCapsuleHalfHeight(Data->CapsuleHalfheight);
	GetCapsuleComponent()->SetCapsuleRadius(Data->CapsuleRadius);

	BodyMesh->SetRelativeLocation(FVector(.0f, .0f, -Data->CapsuleHalfheight));
	BodyMesh->SetSkeletalMesh(UM3GameInstance::GetResourceManager()->GetObjectFromID<USkeletalMesh>(Data->MeshResource));

	FName SocketWeapon("SocketWeapon");
	WeaponCapsuleComponent->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform, SocketWeapon);
	WeaponCapsuleComponent->SetCapsuleHalfHeight(Data->WeaponCapsuleHalfheight);
	WeaponCapsuleComponent->SetCapsuleRadius(Data->WeaponCapsuleRadius);

	SetAnimation(MonsterInfo.ID);

	TArray<FString> List;
	Data->DropList.ParseIntoArray(List, TEXT("/"));
	for (int i = 0; i < List.Num(); i++)
	{
		TArray<FString> ListTwo;
		List[i].ParseIntoArray(ListTwo, TEXT(","));
		FMonsterDropTable MonsterDropTable;
		MonsterDropTable.Index = FCString::Atoi(*ListTwo[0]);
		MonsterDropTable.Rate =  FCString::Atof(*ListTwo[1]);
		DropTable.Add(MonsterDropTable);
		UM3GameInstance::GetItemManager()->AsyncItemResourceLoad(EItemType::RESOURCE, MonsterDropTable.Index);
	}
	BuildFSM(Data->FSMStart, Data->FSMList);
}

void AMonsterCharacter::SetAnimation(int MonsterID)
{
	UClass* Class = UM3GameInstance::GetAnimationManager()->GetMonsterABP(MonsterID);
	BodyMesh->SetAnimInstanceClass(Class);
	UAnimInstance* AnimInstance = BodyMesh->GetAnimInstance();
	UMonsterAnimInstance* MonsterAnimInstance = Cast<UMonsterAnimInstance>(AnimInstance);
	if (MonsterAnimInstance) MonsterAnimInstance->OwnerCharacter = this;
}

UMonsterAnimInstance* AMonsterCharacter::GetAnimation()
{	
	return Cast<UMonsterAnimInstance>(BodyMesh->GetAnimInstance());
}

void AMonsterCharacter::ApplyGravity(bool is_ture)
{
	if (is_ture)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	}
}

void AMonsterCharacter::BuildFSM(EMonsterState Start, FString& Data)
{
	if (MonsterController)
	{
		UMonsterFiniteStateMachine* MonsterFiniteStateMachine = MonsterController->MonsterFiniteStateMachine;
		TArray<FString> List;
		Data.ParseIntoArray(List, TEXT("/"));
		for (int i = 0; i < List.Num(); i++)
		{
			TArray<FString> ListTwo;
			List[i].ParseIntoArray(ListTwo, TEXT(","));
			MonsterFiniteStateMachine->AddFiniteState(
				(EMonsterState)FCString::Atoi(*ListTwo[0]),
				(EMonsterEvent)FCString::Atoi(*ListTwo[1]),
				(EMonsterState)FCString::Atoi(*ListTwo[2]));
		}
		MonsterFiniteStateMachine->SetStartState(Start);
	}
}

bool AMonsterCharacter::IsDead()
{
	return MonsterController->MonsterFiniteStateMachine->CurrentPlayerState->State == EMonsterState::DEAD;
}