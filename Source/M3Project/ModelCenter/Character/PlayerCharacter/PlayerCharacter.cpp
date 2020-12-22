#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Base/M3GameInstance.h"
#include "LogicObject/Item/ItemManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "FiniteStateMachine/FiniteState/PlayerFiniteState_React.h"
#include "FiniteStateMachine/FiniteState/PlayerFiniteState_DefualtReact.h"
#include "FiniteStateMachine/FiniteState/PlayerFiniteState_BuildReact.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UI/UIMainWidget.h"
#include "Resource/M3ResourceManager.h"
#include "Resource/SaveData/SaveManager.h"
#include "ModelCenter/Map/MapManager.h"
#include "UI/UIMainWidget.h"
#include "../CharacterManager.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) : ACostomizeCharacter(ObjectInitializer)
{
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	MagnificationValue = 350.0f;
	SpringArmComponent->TargetArmLength = MagnificationValue;

	PlayerFiniteStateMachine = ObjectInitializer.CreateDefaultSubobject<UPlayerFiniteStateMachine>(this, TEXT("FSM"));
	CurrentWeaponType = EWeaponType::NONE;

	SlashWeaponCollisonComponent = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("SlashWeaponCollison"));
	FName SocketRightHand("SocketRightHand");
	SlashWeaponCollisonComponent->SetupAttachment(CharacterPartsComponent.WeaponComponent);
	SlashWeaponCollisonComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetWeaponLength(60.0f);
	if (UE_EDITOR)
	{
		SlashWeaponCollisonComponent->bHiddenInGame = false;
	}
	FBodyInstance* RootBI = GetCapsuleComponent()->GetBodyInstance(NAME_None, false);
	RootBI->bLockXRotation = true;
	RootBI->bLockYRotation = true;

	//Helper
	FName SocketRoot("Root");
	FName SocketHelper("SocketHelper");
	HelperComponent.HelperMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("HelperMesh"));
	FString Path = TEXT("SkeletalMesh'/Game/Resource/Character/Helper/SKM_BuildHelper.SKM_BuildHelper'");
	ConstructorHelpers::FObjectFinder<USkeletalMesh> HelperFinder(*Path);
	HelperComponent.HelperMesh->SetSkeletalMesh(HelperFinder.Object);
	HelperComponent.HelperMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HelperComponent.HelperMesh->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketRoot);
	HelperComponent.HelperMesh->SetRelativeRotation(FRotator(-90.0f, .0f, .0f));
	HelperComponent.ObjectMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ObjectMesh"));
	HelperComponent.ObjectMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HelperComponent.ObjectMesh->AttachToComponent(HelperComponent.HelperMesh, FAttachmentTransformRules::KeepRelativeTransform, SocketHelper);
	//Helper End
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("Magnification", this, &APlayerCharacter::MouseWheel);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpAction);
	PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &APlayerCharacter::MouseLeftClick);
	PlayerInputComponent->BindAction("MouseRight", IE_Pressed, this, &APlayerCharacter::MouseRightClick);
	PlayerInputComponent->BindAction("MouseLeft", IE_Released, this, &APlayerCharacter::MouseLeftRelease);
	PlayerInputComponent->BindAction("MouseRight", IE_Released, this, &APlayerCharacter::MouseRightRelease);
	PlayerInputComponent->BindAction("BattleOn", IE_Pressed, this, &APlayerCharacter::BattleOn);
	PlayerInputComponent->BindAction("BuildOn", IE_Pressed, this, &APlayerCharacter::BuildOn);
	PlayerInputComponent->BindAction("Menu", IE_Pressed, this, &APlayerCharacter::Menu);
	PlayerInputComponent->BindAction("Enter", IE_Pressed, this, &APlayerCharacter::Enter);

#ifdef UE_EDITOR
	//PlayerInputComponent->BindAction("Editor", IE_Pressed, this, &APlayerCharacter::ShowEditorWidget);
#endif // UE_EDITOR
}

void APlayerCharacter::BeginPlay()
{
	FPlayerData& PlayerData = UM3GameInstance::GetSaveManager()->GetPlayerData();
	SetPlayerInfo(PlayerData.PlayerInfo);
	SetActorLocation(PlayerInfo.PlayerLocation);
	CostomizingInformation = PlayerData.CustomizingInformation;
	Super::BeginPlay();
	PlayerFiniteStateMachine->Init(this);
	ChangeWeaponItem(UM3GameInstance::GetItemManager()->GetWeaponItem(PlayerData.EquipmentData.WeaponItemID));
	ChangeEquipmentItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(PlayerData.EquipmentData.CapItemID), EEquipmentsType::CAP);
	ChangeEquipmentItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(PlayerData.EquipmentData.TopItemID), EEquipmentsType::TOP);
	ChangeEquipmentItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(PlayerData.EquipmentData.BottomItemID), EEquipmentsType::BOTTOM);
	ChangeEquipmentItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(PlayerData.EquipmentData.HandsItemID), EEquipmentsType::HANDS);
	ChangeEquipmentItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(PlayerData.EquipmentData.FeetItemID), EEquipmentsType::FEET);

	UM3GameInstance::GetMapManager()->Start(GetActorLocation());
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	PlayerFiniteStateMachine->Tick(DeltaSeconds);
	UM3GameInstance::GetMapManager()->Update(GetActorLocation());
}

void APlayerCharacter::ReBuildStatFromItem()
{
	PlayerInfo.MaxHP = 100;
	PlayerInfo.CurrentHP = PlayerInfo.MaxHP;
	PlayerInfo.AttackPoint = 0;
	PlayerInfo.DeffensPoint = 0;
	if (EquipmentItem.WeaponItem) PlayerInfo.AttackPoint = EquipmentItem.WeaponItem->DefaultInfo.AttackPoint;
	if (EquipmentItem.CapItem) PlayerInfo.DeffensPoint += EquipmentItem.CapItem->DefaultInfo.DefensePoint;
	if (EquipmentItem.BottomItem) PlayerInfo.DeffensPoint += EquipmentItem.BottomItem->DefaultInfo.DefensePoint;
	if (EquipmentItem.TopItem) PlayerInfo.DeffensPoint += EquipmentItem.TopItem->DefaultInfo.DefensePoint;
	if (EquipmentItem.HandsItem) PlayerInfo.DeffensPoint += EquipmentItem.HandsItem->DefaultInfo.DefensePoint;
	if (EquipmentItem.FeetItem) PlayerInfo.DeffensPoint += EquipmentItem.FeetItem->DefaultInfo.DefensePoint;
	if (UUIMainWidget::GetInstance())
	{
		UUIMainWidget::GetInstance()->DefualtUI->StateBar->SetMaxHP(PlayerInfo.MaxHP);
	}
}

void APlayerCharacter::ApplyDamage(int Damage, ACharacter* Attacker)
{
	if (PlayerFiniteStateMachine->CurrentPlayerState->State == EPlayerState::DEAD) return;
	PlayerInfo.CurrentHP -= Damage;
	if (PlayerInfo.CurrentHP <= 0)
	{
		PlayerInfo.CurrentHP = 0;
		PlayerFiniteStateMachine->StateEvent(EPlayerEvent::DEAD_START);
	}

	if (UUIMainWidget::GetInstance())
	{
		UUIMainWidget::GetInstance()->DefualtUI->StateBar->Update();
	}

	else if (PlayerFiniteStateMachine->CurrentPlayerState->State == EPlayerState::REACT)
	{
		Cast<UPlayerFiniteState_React>(PlayerFiniteStateMachine->CurrentPlayerState)->React(Attacker);
	}
	else if (PlayerFiniteStateMachine->CurrentPlayerState->State == EPlayerState::DEFUALT_REACT)
	{
		Cast<UPlayerFiniteState_DefualtReact>(PlayerFiniteStateMachine->CurrentPlayerState)->React(Attacker);
	}
	else if (PlayerFiniteStateMachine->CurrentPlayerState->State == EPlayerState::BUILD_REACT)
	{
		Cast<UPlayerFiniteState_BuildReact>(PlayerFiniteStateMachine->CurrentPlayerState)->React(Attacker);
	}
	else
	{
		PlayerFiniteStateMachine->StateEvent(EPlayerEvent::REACT_START);
	}
}

void APlayerCharacter::SetWeaponLength(float Length)
{
	SlashWeaponCollisonComponent->SetRelativeLocation(FVector(.0f, .0f, Length));
	SlashWeaponCollisonComponent->SetCapsuleHalfHeight(Length);
	SlashWeaponCollisonComponent->SetCapsuleRadius(Length * 0.2f);
}

void APlayerCharacter::ChangeBattleMode(bool OnOff)
{
	FName SocketRightHand("SocketRightHand");
	FName SocketLeftHand("SocketLeftHand");
	FName SocketSpine("SocketSpine");

	FVector WeaponPos(.0f, .0f, .0f);
	FVector SubWeaponPos(.0f, .0f, .0f);
	switch (CurrentWeaponType)
	{
	case EWeaponType::NONE:
		break;
	case EWeaponType::TWOHANDED:
		WeaponPos = FVector(.0f, .0f, -30.0f);
		break;
	default:
		break;
	}
	if (OnOff)
	{
		CharacterPartsComponent.WeaponComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketRightHand);
		CharacterPartsComponent.SubWeaponComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketLeftHand);
		CharacterPartsComponent.WeaponComponent->SetRelativeLocation(FVector(.0f, .0f, .0f));
		CharacterPartsComponent.SubWeaponComponent->SetRelativeLocation(FVector(.0f, .0f, .0f));
	}
	else
	{
		CharacterPartsComponent.WeaponComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketSpine);
		CharacterPartsComponent.SubWeaponComponent->AttachToComponent(CharacterPartsComponent.TopComponent, FAttachmentTransformRules::KeepRelativeTransform, SocketSpine);
		CharacterPartsComponent.WeaponComponent->SetRelativeLocation(WeaponPos);
		CharacterPartsComponent.SubWeaponComponent->SetRelativeLocation(SubWeaponPos);
	}
}

UWeaponItem* APlayerCharacter::ChangeWeaponItem(UWeaponItem* Item)
{
	UWeaponItem* OldItem = EquipmentItem.WeaponItem;
	EquipmentItem.WeaponItem = Item;
	if (Item == nullptr)
	{
		CharacterPartsComponent.WeaponComponent->SetStaticMesh(nullptr);
		CurrentWeaponType = EWeaponType::NONE;
		return OldItem;
	}
	UStaticMesh* WeaponMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(Item->DefaultInfo.MeshResource);
	CharacterPartsComponent.WeaponComponent->SetStaticMesh(WeaponMesh);
	CurrentWeaponType = (EWeaponType)Item->DefaultInfo.Type;

	FVector WeaponPos(.0f, .0f, .0f);
	FVector SubWeaponPos(.0f, .0f, .0f);
	switch (CurrentWeaponType)
	{
	case EWeaponType::NONE:
		break;
	case EWeaponType::TWOHANDED:
		WeaponPos = FVector(.0f, .0f, -30.0f);
		break;
	default:
		break;
	}
	CharacterPartsComponent.WeaponComponent->SetRelativeLocation(WeaponPos);
	SetWeaponLength(Item->DefaultInfo.WeaponLenght);
	ReBuildStatFromItem();
	return OldItem;
}

UEquipmentItem* APlayerCharacter::ChangeEquipmentItem(UEquipmentItem* Item, EEquipmentsType Type)
{
	UMaterialInstanceDynamic* BodyMatInst = Cast<UMaterialInstanceDynamic>(CharacterPartsComponent.EarsComponent->GetMaterial(0));

	UStaticMesh* StMesh = nullptr;
	USkeletalMesh* SkMesh = nullptr;
	UEquipmentItem* OldItem = nullptr;
	if (Item)
	{
		if (Type == EEquipmentsType::CAP)
		{
			StMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(Item->DefaultInfo.MeshResource);
		}
		else
		{
			SkMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<USkeletalMesh>(Item->DefaultInfo.MeshResource);
		}
		switch (Type)
		{
		case EEquipmentsType::CAP:
		{
			CharacterPartsComponent.CapComponent->SetStaticMesh(StMesh);
			OldItem = EquipmentItem.CapItem;
			EquipmentItem.CapItem = Item;
		}
		break;
		case EEquipmentsType::TOP:
		{
			CharacterPartsComponent.TopComponent->SetSkeletalMesh(SkMesh);
			CharacterPartsComponent.TopComponent->SetMaterialByName("Skin", BodyMatInst);
			OldItem = EquipmentItem.TopItem;
			EquipmentItem.TopItem = Item;
		}
		break;
		case EEquipmentsType::BOTTOM:
		{
			CharacterPartsComponent.BottomComponent->SetSkeletalMesh(SkMesh);
			CharacterPartsComponent.BottomComponent->SetMaterialByName("Skin", BodyMatInst);
			OldItem = EquipmentItem.BottomItem;
			EquipmentItem.BottomItem = Item;
		}
		break;
		case EEquipmentsType::HANDS:
		{
			CharacterPartsComponent.HandsComponent->SetSkeletalMesh(SkMesh);
			CharacterPartsComponent.HandsComponent->SetMaterialByName("Skin", BodyMatInst);
			OldItem = EquipmentItem.HandsItem;
			EquipmentItem.HandsItem = Item;
		}
		break;
		case EEquipmentsType::FEET:
		{
			CharacterPartsComponent.FeetComponent->SetSkeletalMesh(SkMesh);
			CharacterPartsComponent.FeetComponent->SetMaterialByName("Skin", BodyMatInst);
			OldItem = EquipmentItem.FeetItem;
			EquipmentItem.FeetItem = Item;
		}
		break;
		}
	}
	else
	{
		switch (Type)
		{
		case EEquipmentsType::CAP:
		{
			CharacterPartsComponent.CapComponent->SetStaticMesh(nullptr);
			OldItem = EquipmentItem.CapItem;
			EquipmentItem.CapItem = Item;
		}
		break;
		case EEquipmentsType::TOP:
		{
			SkMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<USkeletalMesh>((CostomizingInformation.IsFemale) ? kTopNude_F : kTopNude);
			CharacterPartsComponent.TopComponent->SetSkeletalMesh(SkMesh);
			CharacterPartsComponent.TopComponent->SetMaterialByName("Skin", BodyMatInst);
			OldItem = EquipmentItem.TopItem;
			EquipmentItem.TopItem = Item;
		}
		break;
		case EEquipmentsType::BOTTOM:
		{
			SkMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<USkeletalMesh>((CostomizingInformation.IsFemale) ? kBottomNude_F : kBottomNude);
			CharacterPartsComponent.BottomComponent->SetSkeletalMesh(SkMesh);
			CharacterPartsComponent.BottomComponent->SetMaterialByName("Skin", BodyMatInst);
			OldItem = EquipmentItem.BottomItem;
			EquipmentItem.BottomItem = Item;
		}
		break;
		case EEquipmentsType::HANDS:
		{
			SkMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<USkeletalMesh>(kHandsNude);
			CharacterPartsComponent.HandsComponent->SetSkeletalMesh(SkMesh);
			CharacterPartsComponent.HandsComponent->SetMaterialByName("Skin", BodyMatInst);
			OldItem = EquipmentItem.HandsItem;
			EquipmentItem.HandsItem = Item;
		}
		break;
		case EEquipmentsType::FEET:
		{
			SkMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<USkeletalMesh>(kFeetNude);
			CharacterPartsComponent.FeetComponent->SetSkeletalMesh(SkMesh);
			CharacterPartsComponent.FeetComponent->SetMaterialByName("Skin", BodyMatInst);
			OldItem = EquipmentItem.FeetItem;
			EquipmentItem.FeetItem = Item;
		}
		break;
		}
	}
	ReBuildStatFromItem();
	return OldItem;
}

FPlayerInfo& APlayerCharacter::GetPlayerInfo()
{
	PlayerInfo.PlayerLocation = GetActorLocation();
	return PlayerInfo;
}

void APlayerCharacter::SetPlayerInfo(FPlayerInfo& Info)
{
	PlayerInfo = Info;
	SetActorLocation(PlayerInfo.PlayerLocation);
}

void APlayerCharacter::Turn(float Rate)
{
	AddControllerYawInput(Rate);
}

void APlayerCharacter::LookUp(float Rate)
{
	AddControllerPitchInput(Rate);
}

void APlayerCharacter::MoveForward(float Value)
{
	PlayerFiniteStateMachine->MoveForward(Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	PlayerFiniteStateMachine->MoveRight(Value);
}

void APlayerCharacter::MouseLeftClick()
{
	PlayerFiniteStateMachine->MouseLeftClick();
}

void APlayerCharacter::MouseRightClick()
{
	PlayerFiniteStateMachine->MouseRightClick();
}

void APlayerCharacter::MouseLeftRelease()
{
	PlayerFiniteStateMachine->MouseLeftRelease();
}

void APlayerCharacter::MouseRightRelease()
{
	PlayerFiniteStateMachine->MouseRightRelease();
}

void APlayerCharacter::MouseWheel(float Value)
{
	PlayerFiniteStateMachine->MouseWheel(Value);
}

void APlayerCharacter::JumpAction()
{
	PlayerFiniteStateMachine->JumpAction();
}

void APlayerCharacter::BattleOn()
{
	PlayerFiniteStateMachine->BattleOn();
}

void APlayerCharacter::BuildOn()
{
	PlayerFiniteStateMachine->BuildOn();
}

void APlayerCharacter::Menu()
{
	UUIMainWidget::GetInstance()->ShowPausedWidget();
}

void APlayerCharacter::Enter()
{
	PlayerFiniteStateMachine->Enter();
}

#ifdef UE_EDITOR
void APlayerCharacter::ShowEditorWidget()
{
	UUIMainWidget::GetInstance()->ShowEditorWidget();
}
#endif // UE_EDITOR