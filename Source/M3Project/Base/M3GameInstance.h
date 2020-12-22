#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Character.h"
#include "M3GameInstance.generated.h"

class UM3ResourceManager;
class UMapManager;
class USaveManager;
class UActorManager;
class UCostomizeManager;
class UAnimationManager;
class UItemManager;
class UCharacterManager;
class UGameTimeManager;

class UQuestSystem;
class UDialogueSystem;
class UCinematicSystem;

class APlayerCharacter;

UCLASS()
class M3PROJECT_API UM3GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	static UM3GameInstance*			GetInstance();
	static UM3ResourceManager*		GetResourceManager();
	static UMapManager*				GetMapManager();
	static USaveManager*			GetSaveManager();
	static UActorManager*			GetActorManager();
	static UCostomizeManager*		GetCostomizeManager();
	static UAnimationManager*		GetAnimationManager();
	static UItemManager*			GetItemManager();
	static UCharacterManager*		GetCharacterManager();
	static UGameTimeManager*		GetGameTimeManager();
	static UQuestSystem*			GetQuestSystem();
	static UDialogueSystem*			GetDialogueSystem();
	static UCinematicSystem*		GetCinematicSystem();
public:
	static APlayerCharacter*		GetPC();
	static APlayerController*		GetPCController();
	static bool						IsPlaying() { return (Instance) ? Instance->bIsPlaying : false; };
public:
	static UM3GameInstance* Instance;
	UM3GameInstance(const FObjectInitializer& ObjectInitializer);
	bool bIsPlaying;
	void Init() override;
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UM3ResourceManager* M3ResourceManager;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UMapManager* MapManager;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USaveManager* SaveManager;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UActorManager* ActorManager;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UCostomizeManager* CostomizeManager;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAnimationManager* AnimationManager;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UItemManager* ItemManager;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UCharacterManager* CharacterManager;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UGameTimeManager* GameTimeManager;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UQuestSystem* QuestSystem;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UDialogueSystem* DialogueSystem;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UCinematicSystem* CinematicSystem;
};