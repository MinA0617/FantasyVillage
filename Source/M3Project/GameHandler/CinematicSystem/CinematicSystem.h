#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "CinematicSystem.generated.h"

UCLASS()
class M3PROJECT_API UCinematicSystem : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY() TMap<FString, ALevelSequenceActor*> CinemaList;
public:
	void SetCinemaList(UWorld* World);
	bool PlayCinema(FString CinemaName, bool IsStopEnd = false);
};
