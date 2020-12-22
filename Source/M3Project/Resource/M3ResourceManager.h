#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "M3ResourceManager.generated.h"


USTRUCT(BlueprintType)
struct FResourceTableResource : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Resource;
};

UCLASS()
class M3PROJECT_API UM3ResourceManager : public UObject
{
	GENERATED_BODY()
public:
	UM3ResourceManager();
	class UDataTable* ResourceDataTable;
public:
	template<class T>
	FUNCTION_NON_NULL_RETURN_START
	T* GetObjectFromID(int ID)
	FUNCTION_NON_NULL_RETURN_END
	{
		FResourceTableResource* Data = ResourceDataTable->FindRow<FResourceTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
		if (!Data) return nullptr;
		FSoftObjectPath Path = Data->Resource;
		FAssetData Asset;
		if (!UAssetManager::Get().GetAssetDataForPath(Path, Asset)) return nullptr;
		T* Result = Cast<T>(Asset.GetAsset());
		return Result;
	};
	bool OrderAsyncLoad(int ID)
	{
		FResourceTableResource* Data = ResourceDataTable->FindRow<FResourceTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
		if (!Data) return false;
		FSoftObjectPath Path = Data->Resource;
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(Path);
		return true;
	}
	bool GetAsyncObjectFromID(int ID, FStreamableDelegate DelegateToCall);
};

