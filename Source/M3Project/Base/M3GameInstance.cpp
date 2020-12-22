#include "M3GameInstance.h"
#include "ModelCenter/Map/MapManager.h"
#include "ModelCenter/Object/ActorManager/ActorManager.h"
#include "ModelCenter/Character/AnimationManager.h"
#include "ModelCenter/Character/Base/CostomizeManager.h"
#include "ModelCenter/Character/CharacterManager.h"
#include "Resource/M3ResourceManager.h"
#include "Resource/SaveData/SaveManager.h"
#include "LogicObject/Item/ItemManager.h"
#include "LogicObject/GameTime/GameTimeManager.h"
#include "GameHandler/QuestSystem/QuestSystem.h"
#include "GameHandler/DialogueSystem/DialogueSystem.h"
#include "GameHandler/CinematicSystem/CinematicSystem.h"

UM3GameInstance* UM3GameInstance::Instance = nullptr;

UM3GameInstance::UM3GameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MapManager = ObjectInitializer.CreateDefaultSubobject<UMapManager>(this, TEXT("MapManager"));
	M3ResourceManager = ObjectInitializer.CreateDefaultSubobject<UM3ResourceManager>(this, TEXT("ResourceManager"));
	SaveManager = ObjectInitializer.CreateDefaultSubobject<USaveManager>(this, TEXT("SaveManager"));
	ActorManager = ObjectInitializer.CreateDefaultSubobject<UActorManager>(this, TEXT("ActorManager"));
	CostomizeManager = ObjectInitializer.CreateDefaultSubobject<UCostomizeManager>(this, TEXT("CostomizeManager"));
	AnimationManager = ObjectInitializer.CreateDefaultSubobject<UAnimationManager>(this, TEXT("AnimationManager"));
	ItemManager = ObjectInitializer.CreateDefaultSubobject<UItemManager>(this, TEXT("ItemManager"));
	CharacterManager = ObjectInitializer.CreateDefaultSubobject<UCharacterManager>(this, TEXT("CharacterManager"));
	GameTimeManager = ObjectInitializer.CreateDefaultSubobject<UGameTimeManager>(this, TEXT("GameTimeManager"));
	QuestSystem = ObjectInitializer.CreateDefaultSubobject<UQuestSystem>(this, TEXT("QuestSystem"));
	DialogueSystem = ObjectInitializer.CreateDefaultSubobject<UDialogueSystem>(this, TEXT("DialogueSystem"));
	CinematicSystem = ObjectInitializer.CreateDefaultSubobject<UCinematicSystem>(this, TEXT("CinematicSystem"));
}

UM3GameInstance* UM3GameInstance::GetInstance()
{
	return Instance;
}

UM3ResourceManager* UM3GameInstance::GetResourceManager()
{
	return UM3GameInstance::GetInstance()->M3ResourceManager;
}

UMapManager* UM3GameInstance::GetMapManager()
{
	return UM3GameInstance::GetInstance()->MapManager;
}

USaveManager* UM3GameInstance::GetSaveManager()
{
	return UM3GameInstance::GetInstance()->SaveManager;
}

UActorManager* UM3GameInstance::GetActorManager()
{
	return UM3GameInstance::GetInstance()->ActorManager;
}

UCostomizeManager* UM3GameInstance::GetCostomizeManager()
{
	return UM3GameInstance::GetInstance()->CostomizeManager;
}

UAnimationManager* UM3GameInstance::GetAnimationManager()
{
	return UM3GameInstance::GetInstance()->AnimationManager;
}

UItemManager* UM3GameInstance::GetItemManager()
{
	return UM3GameInstance::GetInstance()->ItemManager;
}

UCharacterManager* UM3GameInstance::GetCharacterManager()
{
	if (UM3GameInstance::GetInstance())	return UM3GameInstance::GetInstance()->CharacterManager;
	return nullptr;
}

UGameTimeManager* UM3GameInstance::GetGameTimeManager()
{
	if (UM3GameInstance::GetInstance())	return UM3GameInstance::GetInstance()->GameTimeManager;
	return nullptr;
}

UQuestSystem* UM3GameInstance::GetQuestSystem()
{
	if (UM3GameInstance::GetInstance())	return UM3GameInstance::GetInstance()->QuestSystem;
	return nullptr;
}

UDialogueSystem* UM3GameInstance::GetDialogueSystem()
{
	if (UM3GameInstance::GetInstance())	return UM3GameInstance::GetInstance()->DialogueSystem;
	return nullptr;
}

UCinematicSystem* UM3GameInstance::GetCinematicSystem()
{
	if (UM3GameInstance::GetInstance())	return UM3GameInstance::GetInstance()->CinematicSystem;
	return nullptr;
}

APlayerCharacter* UM3GameInstance::GetPC()
{
	if (UM3GameInstance::GetInstance() && UM3GameInstance::GetInstance()->GetWorld())
	{
		for (FConstPlayerControllerIterator Iterator = UM3GameInstance::GetInstance()->GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();
			if (PlayerController)
			{
				APlayerCharacter* PC = Cast<APlayerCharacter>(PlayerController->GetPawn());
				if (PC) return PC;
			}
		}
	}
	return nullptr;
}

APlayerController* UM3GameInstance::GetPCController()
{
	if (UM3GameInstance::GetInstance()->GetWorld())
	{
		return UGameplayStatics::GetPlayerController(UM3GameInstance::GetInstance()->GetWorld(), 0);
	}
	return nullptr;
}

void UM3GameInstance::Init()
{
	CostomizeManager->Init();
	bIsPlaying = false;
	UM3GameInstance::Instance = this;
}
