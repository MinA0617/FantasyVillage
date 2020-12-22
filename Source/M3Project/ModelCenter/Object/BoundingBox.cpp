#include "BoundingBox.h"
#include "Components/StaticMeshComponent.h"

ABoundingBox::ABoundingBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	RootComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Root"));
	for (int i = 0; i < 12; i++)
	{
		FString String = "Line" + FString::FromInt(i);
		FName Name = FName(*String);
		USplineComponent* Spline = ObjectInitializer.CreateDefaultSubobject<USplineComponent>(this, Name);
		Spline->SetWorldTransform(FTransform::Identity);
		LineList.Add(Spline);
		LineList[i]->SetupAttachment(RootComponent);
	}
}

void ABoundingBox::SetSize(int64_3 size)
{
	float HalfX = size.X * 0.5f;
	float HalfY = size.Y * 0.5f;
	float HalfZ = size.Z * 0.5f;

	FVector Scale(0.01f, 0.01f, 0.01f);

	FRotator Rotator(0.0f, 90.0f, 0.0f);

	LineList[0]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(-HalfX, -HalfY, -HalfZ), Scale * size.X));
	LineList[1]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(HalfX, -HalfY, -HalfZ), Scale * size.X));
	LineList[2]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(-HalfX, -HalfY, HalfZ), Scale * size.X));
	LineList[3]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(HalfX, -HalfY, HalfZ), Scale * size.X));

	Rotator = FRotator(0.0f, 0.0f, 0.0f);
	LineList[4]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(-HalfX, -HalfY, -HalfZ), Scale * size.Y));
	LineList[5]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(-HalfX, HalfY, -HalfZ), Scale * size.Y));
	LineList[6]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(-HalfX, -HalfY, HalfZ), Scale * size.Y));
	LineList[7]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(-HalfX, HalfY, HalfZ), Scale * size.Y));

	Rotator = FRotator(90.0f, 0.0f, 0.0f);
	LineList[8]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(-HalfX, -HalfY, -HalfZ), Scale * size.Z));
	LineList[9]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(-HalfX, HalfY, -HalfZ), Scale * size.Z));
	LineList[10]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(HalfX, -HalfY, -HalfZ), Scale * size.Z));
	LineList[11]->SetRelativeTransform(FTransform(FQuat(Rotator), FVector(HalfX, HalfY, -HalfZ), Scale * size.Z));
}


