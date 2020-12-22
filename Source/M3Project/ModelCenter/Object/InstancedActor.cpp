#include "InstancedActor.h"

AInstancedActor::AInstancedActor(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	InstancedMesh = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("RootMesh"));
	RootComponent = InstancedMesh;

	InstancedMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	//InstancedMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Block);
	//InstancedMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel2, ECollisionResponse::ECR_Block);
}

void AInstancedActor::SetCollisionFromType()
{
	switch (Type)
	{
	case 1:
		InstancedMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		InstancedMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		InstancedMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		break;
	case 2:
		InstancedMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		InstancedMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
		InstancedMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		break;
	default:
		break;
	}
}