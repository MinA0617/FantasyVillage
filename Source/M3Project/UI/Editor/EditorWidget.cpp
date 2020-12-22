#include "EditorWidget.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Map/MapManager.h"

void UEditorWidget::Create(FVector Pos)
{
	for (int i = 0; i < BrushSize; i++)
	{
		for (int j = 0; j < BrushSize; j++)
		{
			for (int k = 0; k < BrushSize; k++)
			{
				UM3GameInstance::GetMapManager()->CreateCube(CubeIndex, Pos + FVector(i * kCubeSizeXY, j * kCubeSizeXY, k * kCubeSizeZ), Rotation);
			}
		}
	}
}

void UEditorWidget::Destroy(FVector Pos)
{
	for (int i = 0; i < BrushSize; i++)
	{
		for (int j = 0; j < BrushSize; j++)
		{
			for (int k = 0; k < BrushSize; k++)
			{
				UM3GameInstance::GetMapManager()->DestroyCube(Pos + FVector(i * kCubeSizeXY, j * kCubeSizeXY, k * kCubeSizeZ));
			}
		}
	}
}

void UEditorWidget::SetBrushSize(int Size)
{
	if (Size < 1) BrushSize = 1;
	else if (Size > 100) BrushSize = 100;
	else BrushSize = Size;
}

void UEditorWidget::SetCubeIndex(int Index)
{
	CubeIndex = Index;
}

void UEditorWidget::SetNextRotation()
{
	Rotation++;
	if (Rotation == 4) Rotation = 0;
}