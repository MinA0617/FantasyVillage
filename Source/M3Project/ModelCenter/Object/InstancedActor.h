#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "M3Project.h"
#include "InstancedActor.generated.h"

UCLASS()
class M3PROJECT_API AInstancedActor : public AActor
{
	GENERATED_BODY()
public:	
	AInstancedActor(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(EditDefaultsOnly)
	UInstancedStaticMeshComponent*			InstancedMesh;
	uint8									Type;
	int64									Durability; // 0일 경우 부수지 못한다.
	TArray<int64_3>							DependencyList[4];
public:
	void									SetCollisionFromType();
};
