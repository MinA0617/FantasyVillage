#include "M3GameMode.h"
#include "Base/M3GameInstance.h"
#include "ConstructorHelpers.h"
#include "UI/UIMainWidget.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "ModelCenter/Character/PlayerCharacter/Controller/M3PlayerController.h"
#include "ModelCenter/Map/MapManager.h"
#include "ModelCenter/Object/ActorManager/ActorManager.h"
#include "Resource/SaveData/SaveManager.h"
#include "ConstructorHelpers.h"
#include "ModelCenter/Map/MapManager.h"
#include "GameHandler/CinematicSystem/CinematicSystem.h"
#include "TimerManager.h"

AM3GameMode* AM3GameMode::GameMode = nullptr;

AM3GameMode* AM3GameMode::GetInstance()
{
	return GameMode;
};

AM3GameMode::AM3GameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AM3PlayerController::StaticClass();

	PrimaryActorTick.bCanEverTick = true;

	FString Path = TEXT("WidgetBlueprint'/Game/Resource/UI/BP_UIMainWidget.BP_UIMainWidget_C'");
	ConstructorHelpers::FClassFinder<UUIMainWidget> MainWidget(*Path);
	MainWidgetClass = MainWidget.Class;
}

void AM3GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UM3GameInstance::GetActorManager()->Update(DeltaSeconds);
}

void AM3GameMode::BeginPlay()
{
	Super::BeginPlay();
	GameMode = this;
	UM3GameInstance::GetCinematicSystem()->SetCinemaList(UM3GameInstance::GetInstance()->GetWorld());
	UUIMainWidget* MainWidget = CreateWidget<UUIMainWidget>(GetWorld(), MainWidgetClass, FName("MainWidget"));
	MainWidget->AddToViewport();
	if (UM3GameInstance::GetMapManager()->CurrentLevelName.ToString() == "DefualtLevel")
	{
		UM3GameInstance::GetMapManager()->GetWorldMap()->SpawnSunLight();
	}
}

void AM3GameMode::BeginDestroy()
{
	Super::BeginDestroy();
	GameMode = nullptr;
}

void AM3GameModeProlog::BeginPlay()
{
	Super::BeginPlay();
	UM3GameInstance::GetCinematicSystem()->PlayCinema("LevelSequence01");
}