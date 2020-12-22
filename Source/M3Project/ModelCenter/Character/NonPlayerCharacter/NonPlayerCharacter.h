#pragma once

#include "CoreMinimal.h"
#include "ModelCenter/Character/Base/CostomizeCharacter.h"
#include "NonPlayerCharacter.generated.h"

UENUM()
enum class ENPCType : uint8
{
	DEACON,
	STORE,
	REINFORCE,
	MANUFACTURING,

	GODDESS = 101,
};

USTRUCT(BlueprintType)
struct FNPCInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() ENPCType	NPCIndex;
	UPROPERTY() FString		NPCName;
};

UCLASS()
class M3PROJECT_API ANonPlayerCharacter : public ACostomizeCharacter
{
	GENERATED_BODY()
public:
	ANonPlayerCharacter(const FObjectInitializer& ObjectInitializer);
public:
	FNPCInfo Info;
public:
	void Converse();
};