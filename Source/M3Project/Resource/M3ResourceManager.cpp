#include "M3ResourceManager.h"
#include "ConstructorHelpers.h"
#include "Base/M3GameInstance.h"

UM3ResourceManager::UM3ResourceManager()
{
	FString CubeDataPath = TEXT("DataTable'/Game/Resource/ResourceTable/ResourceTable.ResourceTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_CUBE(*CubeDataPath);
	if (DT_CUBE.Succeeded()) ResourceDataTable = DT_CUBE.Object;
}

bool UM3ResourceManager::GetAsyncObjectFromID(int ID, FStreamableDelegate DelegateToCall)
{
	FResourceTableResource* Data = ResourceDataTable->FindRow<FResourceTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
	if (!Data) return false;
	FSoftObjectPath Path = Data->Resource;
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(Path, DelegateToCall, 0, false, false);
	return true;
};