#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/UIMainWidget.h"
#include "M3GameMode.generated.h"

UCLASS()
class M3PROJECT_API AM3GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	static AM3GameMode* GameMode;
	static AM3GameMode* GetInstance();
public:
	AM3GameMode(const FObjectInitializer& ObjectInitializer);
public:
	void Tick(float DeltaSeconds) override;
	void BeginPlay() override;
	void BeginDestroy() override;
public:
	TSubclassOf<UUIMainWidget> MainWidgetClass;
};

UCLASS()
class M3PROJECT_API AM3GameModeProlog : public AM3GameMode
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
};