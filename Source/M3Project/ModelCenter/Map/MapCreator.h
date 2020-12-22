#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "../Object/CreatingHelperActor.h"
#include "MapCreator.generated.h"

UCLASS()
class M3PROJECT_API UMapCreator : public UObject
{
	GENERATED_BODY()
public:
	UMapCreator(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY() ACreatingHelperActor* HelperActor;
public:
	bool SetActivation(bool bIsActivation);
	void SetCubeMeshActivation(bool bIsActivation);
	bool CreateCube();
	void SetNextIndex(bool IsNext);
	void SetCubeIndex(int Index);
	void SetRotation(int Rotation);
	int GetInventoryIndex() { return InventoryIndex; };
	void SetCubeMesh();
private:
	int CubeMeshID;
	int InventoryIndex;
	int CurrentCubeIndex;
	int CurrentRotation;
};
