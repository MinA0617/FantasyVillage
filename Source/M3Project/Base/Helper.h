#pragma once

#include "CoreMinimal.h"
#include <string>
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "CollisionQueryParams.h"
#include "UObject/UObjectIterator.h"
#include "Helper.generated.h"

UCLASS()
class M3PROJECT_API UHelper : public UObject
{
    GENERATED_BODY()
public:
    static bool SphereCollision(AActor* CollisionActor, const float Radius, TArray<FHitResult>& HitOut, ECollisionChannel TraceChannel = ECC_Pawn);
    static void DrawSphere(UWorld* World, FVector Position, FColor Color, float Radius, float LifeTime);
    static std::string GetClientPath();
};
