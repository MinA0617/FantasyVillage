#include "ItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "Base/M3GameInstance.h"
#include "Resource/M3ResourceManager.h"
#include "ModelCenter/Character/CharacterManager.h"
#include "UI/UIMainWidget.h"
#include "LogicObject/Item/ItemManager.h"

AItemActor::AItemActor(const FObjectInitializer& ObjectInitializer) : AActor(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ItemMesh"));
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Ignore);
	Item = nullptr;
	SetRootComponent(ItemMesh);
}

void AItemActor::BuildFromIndex(EItemType Type, int Index)
{
	switch (Type)
	{
	case EItemType::RESOURCE:
	{
		Item = UM3GameInstance::GetItemManager()->GetResourceItem(Index);
		UResourceItem* RItem = Cast<UResourceItem>(Item);
		ItemMesh->SetStaticMesh(UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(RItem->DefaultInfo.MeshResource));
		break;
	}
	case EItemType::INSTALLATION:
	{
		Item = UM3GameInstance::GetItemManager()->GetInstallationItem(Index);
		UInstallationItem* IItem = Cast<UInstallationItem>(Item);
		ItemMesh->SetStaticMesh(UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(IItem->DefaultInfo.MeshResource));
		ItemMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
		break;
	}
	default:
		break;
	}
	if (!Item) Destroy();
}

void AItemActor::GetItemToInventory()
{
	UM3GameInstance::GetCharacterManager()->Inventory->AddItem(Item);
	UUIMainWidget::GetInstance()->DefualtUI->AddItemList->AddAddItemWidget(Item);
	Destroy();
}