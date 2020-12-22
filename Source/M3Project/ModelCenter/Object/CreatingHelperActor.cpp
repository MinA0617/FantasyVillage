#include "CreatingHelperActor.h"
#include "ConstructorHelpers.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ModelCenter/Map/MapManager.h"
#include "Engine/StaticMesh.h"
#include "Resource/M3ResourceManager.h"

ACreatingHelperActor::ACreatingHelperActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	HelperMesh = ObjectInitializer.CreateDefaultSubobject<UInstancedStaticMeshComponent>(this, TEXT("HelperMesh"));
	CubeMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("CubeMesh"));
	FString Path = TEXT("StaticMesh'/Game/Resource/MapData/Mesh/Helper/SKM_Helper.SKM_Helper'");
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(*Path);
	HelperMesh->SetStaticMesh(MeshFinder.Object);
	CubeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HelperMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(HelperMesh);
	CubeMesh->SetupAttachment(RootComponent);
	CurrentIndex = 0;
	CurrentRotation = 0;
}

void ACreatingHelperActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACreatingHelperActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentIndex == 0) return;
	const FRotator Rotation = UM3GameInstance::GetPC()->CharacterPartsComponent.TopComponent->GetComponentRotation() + FRotator(.0f, 90.0f, .0f);
	const FRotator YRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YRotation).GetUnitAxis(EAxis::X);
	float Offset = Direction.Size() * ((float)CubeOffset + 1.3);
	FVector Pos = UM3GameInstance::GetPC()->GetActorLocation() + FVector(.0f, .0f, -50.0f) + (Direction * (Offset * kCubeSizeXY)) - FVector(kCubeSizeXY / 2, kCubeSizeXY / 2, kCubeSizeZ / 2);
	Pos = FVector(FMath::RoundToInt(Pos.X / kCubeSizeXY) * (float)kCubeSizeXY,
		FMath::RoundToInt(Pos.Y / kCubeSizeXY) * (float)kCubeSizeXY,
		FMath::RoundToInt(Pos.Z / kCubeSizeZ) * (float)kCubeSizeZ)
		+ FVector(kCubeSizeXY / 2, kCubeSizeXY / 2, kCubeSizeZ / 2);
	if (GetActorLocation().Equals(Pos, 1.0f) == false)
	{
		SetActorLocation(Pos);
		SetCubeMeshColor();
	}
}

void ACreatingHelperActor::SetCubeMesh(UStaticMesh* Mesh)
{
	CubeMesh->SetStaticMesh(Mesh);
	UMaterialInstance* OldMat = Cast<UMaterialInstance>(Mesh->GetMaterial(0));
	CubeMesh->SetMaterial(0, OldMat);
	UMaterial* Mat = UM3GameInstance::GetResourceManager()->GetObjectFromID<UMaterial>(20001001);
	if (OldMat && Mat)
	{
		UMaterialInstanceDynamic* NewMatInst = UMaterialInstanceDynamic::Create(Mat, this);
		UTexture* TextureParma = nullptr;
		const FMaterialParameterInfo MaterialParameterInfo("Texture");
		OldMat->GetTextureParameterValue(MaterialParameterInfo, TextureParma);
		NewMatInst->SetTextureParameterValue("Texture", TextureParma);
		NewMatInst->SetScalarParameterValue("Opacity", .6f);
		CubeMesh->SetMaterial(0, NewMatInst);
		SetCubeMeshColor();
	}
}

void ACreatingHelperActor::SetDependency(TArray<int64_3> Dependency_List)
{
	CubeOffset = 0;
	while (HelperMesh->GetInstanceCount() != 0)
	{
		HelperMesh->RemoveInstance(0);
	}
	DependencyList = Dependency_List;
	HelperMesh->AddInstance(FTransform(FVector(0.0f, 0.0f, 0.0f)));
	for (int i = 0; i < DependencyList.Num(); i++)
	{
		HelperMesh->AddInstance(FTransform(FVector(
			DependencyList[i].X * (float)kCubeSizeXY,
			DependencyList[i].Y * (float)kCubeSizeXY,
			DependencyList[i].Z * (float)kCubeSizeZ)));
		CubeOffset = FMath::Max3<int>(CubeOffset, FMath::Abs(DependencyList[i].X), FMath::Abs(DependencyList[i].Y));
	}
}

void ACreatingHelperActor::SetCubeMeshColor()
{
	if (UM3GameInstance::GetMapManager()->CheckObjcet(GetActorLocation(), CurrentIndex, CurrentRotation))
	{
		UMaterialInstanceDynamic* MatInst = Cast<UMaterialInstanceDynamic>(CubeMesh->GetMaterial(0));
		if (MatInst)
		{
			MatInst->SetVectorParameterValue("ColorBurn", FVector(1.0f, 1.0f, 1.0f));
		}
	}
	else
	{
		UMaterialInstanceDynamic* MatInst = Cast<UMaterialInstanceDynamic>(CubeMesh->GetMaterial(0));
		if (MatInst)
		{
			MatInst->SetVectorParameterValue("ColorBurn", FVector(1.0f, .0f, .0f));
		}
	}
}

