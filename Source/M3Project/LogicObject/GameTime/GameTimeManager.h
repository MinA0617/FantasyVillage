#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Resource/SaveData/SaveGameData.h"
#include "TimerManager.h"
#include "GameTimeManager.generated.h"

UCLASS()
class M3PROJECT_API UGameTimeManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION() void RepeatingFunction();
	void SetGameTime(FGameTime& Time) { GameTime = Time; };
	FGameTime GetGameTime() { return GameTime; };
	void Start();
public:
	FGameTime GameTime;
private:
	UPROPERTY() FTimerHandle Handle;
};
