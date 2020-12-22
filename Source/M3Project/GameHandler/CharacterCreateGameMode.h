#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/CharacterCreate/CharacterCreateWidget.h"
#include "CharacterCreateGameMode.generated.h"

UCLASS()
class M3PROJECT_API ACharacterCreateGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	TSubclassOf<UCharacterCreateWidget> CharacterCreateWidgetClass;
	UCharacterCreateWidget* CharacterCreateWidget;
public:
	ACharacterCreateGameMode(const FObjectInitializer& ObjectInitializer);
	void BeginPlay() override;
};
