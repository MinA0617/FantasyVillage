#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "M3Project.h"
#include "Components/SplineComponent.h"
#include "BoundingBox.generated.h"

UCLASS()
class M3PROJECT_API ABoundingBox : public AActor
{
	GENERATED_BODY()
public:
	ABoundingBox(const FObjectInitializer& ObjectInitializer);
	void SetSize(int64_3 size);
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<USplineComponent*> LineList;
};
