#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/NonPlayerCharacter/NonPlayerCharacter.h"
#include "NonPlayerCharacter_Goddess.generated.h"

UCLASS()
class M3PROJECT_API ANonPlayerCharacter_Goddess : public ANonPlayerCharacter
{
	GENERATED_BODY()
public:
	ANonPlayerCharacter_Goddess(const FObjectInitializer& ObjectInitializer);
public:
	void BeginPlay() override;
};
