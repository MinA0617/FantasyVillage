#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogicObject/Item/ResourceItem.h"
#include "ItemActor.generated.h"

UCLASS()
class M3PROJECT_API AItemActor : public AActor
{
	GENERATED_BODY()
public:	
	AItemActor(const FObjectInitializer& ObjectInitializer);
	UPROPERTY() UStaticMeshComponent* ItemMesh;
	UPROPERTY() UItemBase* Item;
public:
	void BuildFromIndex(EItemType Type, int Index);
	void GetItemToInventory();
};
