#include "CostomizeCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Base/M3GameInstance.h"
#include "GameFramework/Controller.h"
#include "ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CostomizeManager.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"

ACostomizeCharacter::ACostomizeCharacter(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	CharacterPartsComponent.TopComponent = GetMesh();
	CharacterPartsComponent.HeadComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("HeadComponent"));
	CharacterPartsComponent.EarsComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("EarsComponent"));
	CharacterPartsComponent.NoseComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("NoseComponent"));
	CharacterPartsComponent.HairComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("HairComponent"));
	CharacterPartsComponent.CapComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("CapComponent"));
	CharacterPartsComponent.BottomComponent = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("BottomComponent"));
	CharacterPartsComponent.HandsComponent = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("HandComponent"));
	CharacterPartsComponent.FeetComponent = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FootComponent"));
	CharacterPartsComponent.WeaponComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("WeaponComponent"));
	CharacterPartsComponent.SubWeaponComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("SubWeaponComponent"));
	CharacterPartsComponent.HeadComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.EarsComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.NoseComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.HairComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.CapComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.TopComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.BottomComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.HandsComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.FeetComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.WeaponComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.SubWeaponComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CharacterPartsComponent.WeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CharacterPartsComponent.SubWeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	CharacterPartsComponent.TopComponent->SetRelativeScale3D(FVector(1.3, 1.3, 1.3));
	CharacterPartsComponent.TopComponent->SetRelativeLocation(FVector(0, 0, -88));
	CharacterPartsComponent.TopComponent->SetRelativeRotation(FRotator(0, -90, 0));

	GetCapsuleComponent()->SetCapsuleHalfHeight(88);
	GetCapsuleComponent()->SetCapsuleRadius(40);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Ignore);

	FName SocketHead("SocketHead");
	FName SocketNose("SocketNose");
	FName SocketRightHand("SocketRightHand");
	FName SocketLeftHand("SocketLeftHand");
	FName SocketSpine("SocketSpine");

	FString Path;
	Path = TEXT("StaticMesh'/Game/Resource/Character/Mesh/Head/STM_Face_01.STM_Face_01'");
	ConstructorHelpers::FObjectFinder<UStaticMesh> HeadFinder(*Path);
	CharacterPartsComponent.HeadComponent->SetStaticMesh(HeadFinder.Object);
	Path = TEXT("StaticMesh'/Game/Resource/Character/Mesh/Head/STM_Ears_01.STM_Ears_01'");
	ConstructorHelpers::FObjectFinder<UStaticMesh> EarsFinder(*Path);
	CharacterPartsComponent.EarsComponent->SetStaticMesh(EarsFinder.Object);
	Path = TEXT("StaticMesh'/Game/Resource/Character/Mesh/Head/STM_Nose_01.STM_Nose_01'");
	ConstructorHelpers::FObjectFinder<UStaticMesh> NoseFinder(*Path);
	CharacterPartsComponent.NoseComponent->SetStaticMesh(NoseFinder.Object);
	Path = TEXT("SkeletalMesh'/Game/Resource/Character/Mesh/Nude/Nude_Top.Nude_Top'");
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TopFinder(*Path);
	CharacterPartsComponent.TopComponent->SetSkeletalMesh(TopFinder.Object);
	Path = TEXT("SkeletalMesh'/Game/Resource/Character/Mesh/Nude/Nude_Bottom.Nude_Bottom'");
	ConstructorHelpers::FObjectFinder<USkeletalMesh> BottomFinder(*Path);
	CharacterPartsComponent.BottomComponent->SetSkeletalMesh(BottomFinder.Object);
	Path = TEXT("SkeletalMesh'/Game/Resource/Character/Mesh/Nude/Nude_Hands.Nude_Hands'");
	ConstructorHelpers::FObjectFinder<USkeletalMesh> HandsFinder(*Path);
	CharacterPartsComponent.HandsComponent->SetSkeletalMesh(HandsFinder.Object);
	Path = TEXT("SkeletalMesh'/Game/Resource/Character/Mesh/Nude/Nude_Feet.Nude_Feet'");
	ConstructorHelpers::FObjectFinder<USkeletalMesh> FeetFinder(*Path);
	CharacterPartsComponent.FeetComponent->SetSkeletalMesh(FeetFinder.Object);

	CharacterPartsComponent.HeadComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketHead);
	CharacterPartsComponent.EarsComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketHead);
	CharacterPartsComponent.NoseComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketNose);
	CharacterPartsComponent.HairComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketHead);
	CharacterPartsComponent.CapComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketHead);
	CharacterPartsComponent.WeaponComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketSpine);
	CharacterPartsComponent.SubWeaponComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketSpine);

	CharacterPartsComponent.BottomComponent->SetMasterPoseComponent(CharacterPartsComponent.TopComponent);
	CharacterPartsComponent.BottomComponent->SetupAttachment(CharacterPartsComponent.TopComponent);
	CharacterPartsComponent.HandsComponent->SetMasterPoseComponent(CharacterPartsComponent.TopComponent);
	CharacterPartsComponent.HandsComponent->SetupAttachment(CharacterPartsComponent.TopComponent);
	CharacterPartsComponent.FeetComponent->SetMasterPoseComponent(CharacterPartsComponent.TopComponent);
	CharacterPartsComponent.FeetComponent->SetupAttachment(CharacterPartsComponent.TopComponent);

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1000.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	// Camera Setup
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->ProbeChannel = ECollisionChannel::ECC_EngineTraceChannel3;
	SpringArmComponent->SetRelativeLocation(FVector(.0f, .0f, 40.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	// Camera Setup

	ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(TEXT("AnimBlueprint'/Game/Resource/Character/Animation/ABP_Defualt.ABP_Defualt_C'"));
	SetAnimation(AnimBP.Class);

	if (UE_EDITOR)
	{
		GetCapsuleComponent()->bHiddenInGame = false;
	}
}

void ACostomizeCharacter::BeginPlay()
{
	Super::BeginPlay();
	UM3GameInstance::GetCostomizeManager()->SetCostomize(this);
}

void ACostomizeCharacter::SetAnimation(UClass* AnimClass)
{
	CharacterPartsComponent.TopComponent->SetAnimInstanceClass(AnimClass);
	UAnimInstance* AnimInstance = CharacterPartsComponent.TopComponent->GetAnimInstance();
	UPlayerAnimInstance* PlayerAnimInstance = Cast<UPlayerAnimInstance>(AnimInstance);
	if(PlayerAnimInstance) PlayerAnimInstance->OwnerCharacter = Cast<APlayerCharacter>(this);
}

UAnimInstance* ACostomizeCharacter::GetAnimation()
{
	return CharacterPartsComponent.TopComponent->GetAnimInstance();
}

void ACostomizeCharacter::ApplyGravity(bool is_ture)
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

void ACostomizeCharacter::SetupSex(bool IsFemale)
{
	UMaterialInstanceDynamic* BodyMatInst = Cast<UMaterialInstanceDynamic>(CharacterPartsComponent.EarsComponent->GetMaterial(0));
	if (EquipmentItem.TopItem == nullptr)
	{
		USkeletalMesh* Top = UM3GameInstance::GetResourceManager()->GetObjectFromID<USkeletalMesh>((IsFemale) ? kTopNude_F : kTopNude);
		CharacterPartsComponent.TopComponent->SetSkeletalMesh(Top);
		CharacterPartsComponent.TopComponent->SetMaterialByName("Skin", BodyMatInst);
	}
	if (EquipmentItem.BottomItem == nullptr)
	{
		USkeletalMesh* Bottom = UM3GameInstance::GetResourceManager()->GetObjectFromID<USkeletalMesh>((IsFemale) ? kBottomNude_F : kBottomNude);
		CharacterPartsComponent.BottomComponent->SetSkeletalMesh(Bottom);
		CharacterPartsComponent.BottomComponent->SetMaterialByName("Skin", BodyMatInst);
	}
	CostomizingInformation.IsFemale = IsFemale;
}