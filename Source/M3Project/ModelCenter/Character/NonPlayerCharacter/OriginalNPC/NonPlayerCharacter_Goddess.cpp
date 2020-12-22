#include "NonPlayerCharacter_Goddess.h"
#include "Base/M3GameInstance.h"
#include "ConstructorHelpers.h"
#include "ModelCenter/Character/Base/CostomizeManager.h"

ANonPlayerCharacter_Goddess::ANonPlayerCharacter_Goddess(const FObjectInitializer& ObjectInitializer) : ANonPlayerCharacter(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	Info.NPCIndex = ENPCType::GODDESS;

	FString Path;
	Path = TEXT("SkeletalMesh'/Game/Resource/Character/Mesh/Item/Equipment/Top/SKM_OnePiece_01.SKM_OnePiece_01'");
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TopFinder(*Path);
	CharacterPartsComponent.TopComponent->SetSkeletalMesh(TopFinder.Object);
	EquipmentItem.TopItem = ObjectInitializer.CreateDefaultSubobject<UEquipmentItem>(this, "DummyItem");

	CostomizingInformation.IsFemale = true;

	CostomizingInformation.SkinColor = FColor(247, 221, 196);
	CostomizingInformation.HeadID = 2;
	CostomizingInformation.HairID = 3;
	CostomizingInformation.HairColor = FColor(184, 142, 95);

	CostomizingInformation.EyeID = 2;
	CostomizingInformation.EyeColor = FColor(69, 48, 43);
	CostomizingInformation.EyeHeight =		 0.352f;
	CostomizingInformation.EyeInterval = 	 0.559f;
	CostomizingInformation.EyeSize = 		 0.494f;
	CostomizingInformation.EyeRoation = 	 0.559f;
	CostomizingInformation.EyeStretch = 	 0.798f;

	CostomizingInformation.EyebrowID = 3;
	CostomizingInformation.EyeborwColor = FColor(57, 41, 28);
	CostomizingInformation.EyebrowHeight = 	 0.326f;
	CostomizingInformation.EyebrowInterval = 0.559f;
	CostomizingInformation.EyebrowSize = 	 0.365f;
	CostomizingInformation.EyebrowRoation =	 0.572f;
	CostomizingInformation.EyebrowStretch =  0.552f;

	CostomizingInformation.MouseID = 4;
	CostomizingInformation.MouseColor = FColor(231, 26, 56);
	CostomizingInformation.MouseHeight = 	 0.210f;
	CostomizingInformation.MouseSize = 		 0.113f;
	CostomizingInformation.MouseStretch =    0.326f;

	CostomizingInformation.NoseID = 1;
	CostomizingInformation.NoseHeight = 0.262f;
	CostomizingInformation.NoseSize = 0.171f;
	CostomizingInformation.NoseStretch = 0.106f;

	CostomizingInformation.EarsID = 0;
}

void ANonPlayerCharacter_Goddess::BeginPlay()
{
	Super::BeginPlay();
	UM3GameInstance::GetCostomizeManager()->SetCostomize(this);
}