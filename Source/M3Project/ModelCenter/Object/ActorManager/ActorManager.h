#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActorManager.generated.h"

const float kTickCommandRate = 0.3f;

class CCommand;

UCLASS()
class M3PROJECT_API UActorManager : public UObject
{
	GENERATED_BODY()
public:	
	UActorManager();
public:
	void Update(float DeltaTime);
	void BeginDestroy() override;
	void AddCommand(CCommand* Command);
	void Clear();
};


