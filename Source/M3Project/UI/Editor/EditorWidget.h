#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EditorWidget.generated.h"

UCLASS()
class M3PROJECT_API UEditorWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UEditorWidget();
public:
	UFUNCTION(BlueprintCallable) void Create(FVector Pos);
	UFUNCTION(BlueprintCallable) void Destroy(FVector Pos);
	UFUNCTION(BlueprintCallable) void SetBrushSize(int Size);
	UFUNCTION(BlueprintCallable) void SetCubeIndex(int Index);
	UFUNCTION(BlueprintCallable) void SetNextRotation();
private:
	int BrushSize;
	int CubeIndex;
	int Rotation;
};
