#pragma once

#include "CoreMinimal.h"
#include "GameHandler/M3GameMode.h"
#include "Engine/DirectionalLight.h"
#include "Components/BillboardComponent.h"
#include "SunLight.generated.h"

UCLASS()
class M3PROJECT_API ASunLight : public AActor
{
	GENERATED_BODY()
public:
	ASunLight(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY()	ADirectionalLight* SunDirectionalLight;
	UPROPERTY() UStaticMeshComponent* SunTexture;
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void LightUpdate(FGameTime& GameTime);
};
