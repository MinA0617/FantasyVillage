#include "CharacterCreateGameMode.h"
#include "ConstructorHelpers.h"
#include "Base/M3GameInstance.h"
#include "Resource/SaveData/SaveManager.h"
#include "ModelCenter/Character/Base/CostomizeCharacter.h"
#include "ModelCenter/Character/Base/CostomizeManager.h"

ACharacterCreateGameMode::ACharacterCreateGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FString Path = TEXT("WidgetBlueprint'/Game/Resource/UI/CharacterCreate/BP_CharacterCreateWidget.BP_CharacterCreateWidget_C'");
	ConstructorHelpers::FClassFinder<UCharacterCreateWidget> CCWidget(*Path);
	CharacterCreateWidgetClass = CCWidget.Class;
	DefaultPawnClass = ACostomizeCharacter::StaticClass();
	ReplaySpectatorPlayerControllerClass = APlayerController::StaticClass();
}

void ACharacterCreateGameMode::BeginPlay()
{
	CharacterCreateWidget = CreateWidget<UCharacterCreateWidget>(GetWorld(), CharacterCreateWidgetClass, FName("CCWidget"));
	CharacterCreateWidget->AddToViewport();


	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true;
			PlayerController->bEnableMouseOverEvents = true;
			ACostomizeCharacter* PC = Cast<ACostomizeCharacter>(PlayerController->GetPawnOrSpectator());
			if (PC)
			{
				PC->SetActorLocation(FVector(.0f, .0f, 188.200104));
				PC->SetActorRotation(FQuat(FRotator(.0f, .0f, .0f)));
				PC->CharacterPartsComponent.TopComponent->SetRelativeRotation(FQuat(FRotator(.0f, 90.0f, .0f)));

				FCustomizingInformation* CustomizingInformation = &(PC->CostomizingInformation);
				CustomizingInformation->IsFemale = false;
				CustomizingInformation->SkinColor = FColor(233, 203, 167);
				CustomizingInformation->HairColor = FColor(43, 41, 41);
				CustomizingInformation->EyeColor = FColor(43, 41, 41);
				CustomizingInformation->EyeborwColor = FColor(43, 41, 41);
				CustomizingInformation->MouseColor = FColor(244, 135, 106);
				CustomizingInformation->HeadID = 0;
				CustomizingInformation->HairID = 0;
				CustomizingInformation->EyeID = 0;
				CustomizingInformation->EyeHeight = .5f;
				CustomizingInformation->EyeInterval = .5f;
				CustomizingInformation->EyeSize = .5f;
				CustomizingInformation->EyeRoation = .5f;
				CustomizingInformation->EyeStretch = .5f;
				CustomizingInformation->EyebrowID = 0;
				CustomizingInformation->EyebrowHeight = .5f;
				CustomizingInformation->EyebrowInterval = .5f;
				CustomizingInformation->EyebrowSize = .5f;
				CustomizingInformation->EyebrowRoation = .5f;
				CustomizingInformation->EyebrowStretch = .5f;
				CustomizingInformation->MouseID = 0;
				CustomizingInformation->MouseHeight = .5f;
				CustomizingInformation->MouseSize = .5f;
				CustomizingInformation->MouseStretch = .5f;
				CustomizingInformation->NoseID = 0;
				CustomizingInformation->NoseHeight = .5f;
				CustomizingInformation->NoseSize = .5f;
				CustomizingInformation->NoseStretch = .5f;
				CustomizingInformation->EarsID = 0;

				CharacterCreateWidget->CostomizeWidget->SetOwner(PC);
				UM3GameInstance::GetCostomizeManager()->SetCostomize(PC);
				break;

			}
		}
	}
	UM3GameInstance::GetSaveManager()->GetPlayerData().PlayerInfo.PlayerLocation = FVector(-720.0f, .0f, 150.0f);
}