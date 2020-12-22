#include "SunLight.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "Components/DirectionalLightComponent.h"
#include "Base/M3GameInstance.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"

ASunLight::ASunLight(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	UStaticMeshComponent* StaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Root"));
	SetRootComponent(StaticMeshComponent);
	SunTexture = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Sun"));
	FString Path = TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'");
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(*Path);
	Path = TEXT("Material'/Game/Resource/MapData/Material/Environment/MAT_Sun.MAT_Sun'");
	ConstructorHelpers::FObjectFinder<UMaterial> Tex(*Path);
	SunTexture->SetStaticMesh(Mesh.Object);
	SunTexture->SetMaterial(0, Tex.Object);
	SunTexture->SetupAttachment(StaticMeshComponent);
	SunTexture->SetRelativeScale3D(FVector(20.0f));
	SunTexture->SetRelativeRotation(FQuat(FRotator(-90.0f, .0f, .0f)));
	SunTexture->SetRelativeLocation(FVector(-10000.0f, .0f, .0f));
	PrimaryActorTick.bCanEverTick = true;
}

void ASunLight::BeginPlay()
{
	Super::BeginPlay();
	int ActorNum = GetLevel()->Actors.Num();
	for (int i = 0; i < ActorNum; i++)
	{
		SunDirectionalLight = Cast<ADirectionalLight>(GetLevel()->Actors[i]);
		if (SunDirectionalLight) break;
	}
	if (SunDirectionalLight)
	{
		SunDirectionalLight->SetMobility(EComponentMobility::Movable);
		SunDirectionalLight->SetBrightness(6.0f);
		if (SunDirectionalLight->IsValidLowLevel())
		{
			UDirectionalLightComponent* GetTryLight = Cast<UDirectionalLightComponent>(SunDirectionalLight->GetComponentByClass(UDirectionalLightComponent::StaticClass()));
			GetTryLight->bUsedAsAtmosphereSunLight = true;
		}
	}
}

void ASunLight::Tick(float DeltaTime)
{
	//SetActorLocation(UM3GameInstance::GetPC()->GetActorLocation());
}

void ASunLight::LightUpdate(FGameTime& GameTime)
{
	const int ConvertTime = GameTime.Hour * 3600 + GameTime.Minute * 60 + GameTime.Second;
	const float Pitch = ((ConvertTime * 360.0f) / 86400.0f) + 90.0f;

	if(SunDirectionalLight) SunDirectionalLight->SetActorRotation(FQuat(FRotator(Pitch, 45.0f, .0f)));
	SetActorRotation(FQuat(FRotator(Pitch, 45.0f, .0f)));

	if (GameTime.Hour >= 6 && GameTime.Hour < 18)
	{
		SunTexture->SetHiddenInGame(false);
	}
	else
	{
		SunTexture->SetHiddenInGame(true);
	}
}