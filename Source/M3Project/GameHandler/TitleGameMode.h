#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/Title/TitleWidget.h"
#include "TitleGameMode.generated.h"

UCLASS()
class M3PROJECT_API ATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATitleGameMode(const FObjectInitializer& ObjectInitializer);
public:
	void BeginPlay() override;
public:
	TSubclassOf<UTitleWidget> TitleWidgetClass;
};
