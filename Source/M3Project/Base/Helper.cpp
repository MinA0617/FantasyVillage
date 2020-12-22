#include "Helper.h"
#include "DrawDebugHelpers.h"
#include <direct.h>

bool UHelper::SphereCollision(AActor* CollisionActor, const float Radius, TArray<FHitResult>& HitOut, ECollisionChannel TraceChannel)
{
    FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, CollisionActor);
    TraceParams.bTraceComplex = true;
    TraceParams.bReturnPhysicalMaterial = false;

    return CollisionActor->GetWorld()->SweepMultiByChannel(HitOut,
        CollisionActor->GetActorLocation(),
        CollisionActor->GetActorLocation() + FVector(.0f, .0f, .1f), FQuat(), TraceChannel, FCollisionShape::MakeSphere(Radius), TraceParams);
}

void UHelper::DrawSphere(UWorld* World, FVector Position, FColor Color, float Radius, float LifeTime)
{
    DrawCircle(World, Position, FVector(1.0f, 0.0f, 0.0f), FVector(0.0f, 1.0f, 0.0f), Color, Radius, 10, false, LifeTime);
    DrawCircle(World, Position, FVector(0.0f, 1.0f, 0.0f), FVector(0.0f, 0.0f, 1.0f), Color, Radius, 10, false, LifeTime);
    DrawCircle(World, Position, FVector(0.0f, 0.0f, 1.0f), FVector(1.0f, 0.0f, 0.0f), Color, Radius, 10, false, LifeTime);
}

std::string UHelper::GetClientPath()
{
    char curDir[1000];
    _getcwd(curDir, 1000);
    std::string Path = curDir;
    std::string Result;
    for (int i = 0; i < Path.size(); i++)
    {
        if (Path[i] == '\\')
        {
            Result += '/';
        }
        else
        {
            Result += Path[i];
        }
    }
    return Result;
}