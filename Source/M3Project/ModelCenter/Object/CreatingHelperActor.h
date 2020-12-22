#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base/Type.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "CreatingHelperActor.generated.h"

UCLASS()
class M3PROJECT_API ACreatingHelperActor : public AActor
{
	GENERATED_BODY()
public:	
	ACreatingHelperActor(const FObjectInitializer& ObjectInitializer);
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	void SetCubeMesh(UStaticMesh* Mesh);
	void SetDependency(TArray<int64_3> Dependency_List);
	void SetCubeMeshColor();
public:
	int											CurrentIndex;
	int											CurrentRotation;
private:
	UPROPERTY() UStaticMeshComponent*			CubeMesh;
	UPROPERTY() UInstancedStaticMeshComponent*	HelperMesh;
	TArray<int64_3>								DependencyList;
	int											CubeOffset;
};
