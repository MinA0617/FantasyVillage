#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EditorHandler.generated.h"

UCLASS()
class M3PROJECT_API UEditorHandler : public UObject
{
	GENERATED_BODY()
public:
	static void EditorPlay();
};
