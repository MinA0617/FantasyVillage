#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"
#include "Base/M3GameInstance.h"
#include "Resource/SaveData/SaveZoneData.h"
#include "LogicObject/Item/ItemManager.h"
#include "LogicObject/GameTime/GameTimeManager.h"
#include "ModelCenter/Character/CharacterManager.h"
#include "ModelCenter/Map/MapManager.h"
#include "ModelCenter/Object/ActorManager/ActorManager.h"
#include "GameHandler/M3GameMode.h"
#include "GameHandler/CinematicSystem/CinematicSystem.h"
#include "EditMapCreator.h"
#include <string>
#include <direct.h>

USaveManager::USaveManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentGameData = nullptr;
	bIsEditorMode = false;
	IsLoad = false;
}

int USaveManager::GetIndex()
{
	if (bIsEditorMode || CurrentGameData == nullptr)
	{
		return -1;
	}
	else
	{
		return CurrentGameData->SlotRealIndex;
	}
}

void USaveManager::NewEditData()
{
	USaveGameData* NewGameData = nullptr;
	FString SlotName = "Defualt";
	USaveGame* GameData = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	NewGameData = Cast<USaveGameData>(GameData);
	if (NewGameData == nullptr)
	{
		NewGameData = NewObject<USaveGameData>();
		NewGameData->SlotName = SlotName;
		NewGameData->SlotIndex = 0;
		NewGameData->SlotRealIndex = 0;
		NewGameData->LevelName = "DefualtLevel";
		NewGameData->PlayerData.QuestSwitchList.SetNum((int)EQuestEnum::__MAX__);
		CurrentGameData = NewGameData;
	}
	UEditMapCreator::Create(NewGameData);
	FPlatformProcess::UserSettingsDir();
	UGameplayStatics::SaveGameToSlot(NewGameData, NewGameData->SlotName, NewGameData->SlotIndex);
}

bool USaveManager::NewData(int GameDataIndex)
{
	if (GameDataIndex >= kMaxSaveSlot) return false;

	USaveGameData* NewGameData = nullptr;
	FString SlotName = "Slot" + FString::FromInt(GameDataIndex);
	USaveGame* GameData = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	NewGameData = Cast<USaveGameData>(GameData);
	if (NewGameData == nullptr)
	{
		NewGameData = NewObject<USaveGameData>();
		NewGameData->SlotName = SlotName;
		NewGameData->SlotIndex = 0;
		NewGameData->SlotRealIndex = GameDataIndex;
		NewGameData->LevelName = "CharacterCreateLevel";
	}
	else return false;

	GameData = UGameplayStatics::LoadGameFromSlot(FString("Defualt"), 0);
	if (GameData == nullptr)
	{
		NewEditData();
		GameData = UGameplayStatics::LoadGameFromSlot(FString("Defualt"), 0);
	}
	USaveGameData* DefualtData = Cast<USaveGameData>(GameData);

	for (int ZoneX = 0; ZoneX < kMapSizeXY; ZoneX++)
	{
		for (int ZoneY = 0; ZoneY < kMapSizeXY; ZoneY++)
		{
			FZoneData Output;
			if (LoadZoneData(-1, Output, ZoneX, ZoneY) == false) return false;
			if (SaveZoneData(NewGameData->SlotRealIndex, Output, ZoneX, ZoneY) == false) return false;
		}
	}

	NewGameData->NPCData.NPCDataList = DefualtData->NPCData.NPCDataList;
	NewGameData->PlayerData.QuestSwitchList.SetNum((int)EQuestEnum::__MAX__);
	NewGameData->GameTime.Hour = kStartHour;

	return UGameplayStatics::SaveGameToSlot(NewGameData, NewGameData->SlotName, NewGameData->SlotIndex);
}

bool USaveManager::LoadData(int GameDataIndex)
{
	if (GameDataIndex >= kMaxSaveSlot) return false;

	FString SlotName = "Slot" + FString::FromInt(GameDataIndex);
	USaveGame* GameData = UGameplayStatics::LoadGameFromSlot(FString(SlotName), 0);
	CurrentGameData = Cast<USaveGameData>(GameData);
	if (CurrentGameData == nullptr) return false;
	IsLoad = true;
	UM3GameInstance::GetQuestSystem()->SetSwitchList(CurrentGameData->PlayerData.QuestSwitchList);
	UM3GameInstance::GetGameTimeManager()->SetGameTime(CurrentGameData->GameTime);
	UM3GameInstance::GetCharacterManager()->BuildNPCData(CurrentGameData->NPCData);
	UM3GameInstance::GetCharacterManager()->Inventory->SetBuildInventoryData(CurrentGameData->PlayerData.InventoryData);
	UM3GameInstance::GetGameTimeManager()->Start();
	UM3GameInstance::GetInstance()->bIsPlaying = true;
	OpenGameLevel(CurrentGameData->LevelName);
	return true;
}

bool USaveManager::DeleteData(int GameDataIndex)
{
	if (GameDataIndex >= kMaxSaveSlot) return false;

	std::string Path;
	if (UE_EDITOR)
	{
		Path += "D:/M3Project";
	}
	else
	{
		Path += UHelper::GetClientPath();
		Path += "/MapData/" + std::to_string(GameDataIndex);
		Path += "l";
	}
	for (int i = 0; i < kMapSizeXY; i++)
	{
		for (int j = 0; j < kMapSizeXY; j++)
		{
			std::string TempPath = Path + std::to_string(i << 16 | j);
			TempPath += ".dat";
			remove(TempPath.c_str());
		}
	}

	FString SlotName = "Slot" + FString::FromInt(GameDataIndex);
	return UGameplayStatics::DeleteGameInSlot(FString(SlotName), 0);
}

FGameSlotData USaveManager::GetSlotData(int Index)
{
	FString SlotName = "Slot" + FString::FromInt(Index);
	USaveGame* GameData = UGameplayStatics::LoadGameFromSlot(FString(SlotName), 0);
	CurrentGameData = Cast<USaveGameData>(GameData);
	if (CurrentGameData == nullptr)
	{
		FGameSlotData SlotData;
		SlotData.bIsNotData = true;
		return SlotData;
	}
	else
	{
		FGameSlotData SlotData;
		SlotData.bIsNotData = false;
		SlotData.CharacterName = CurrentGameData->PlayerData.PlayerInfo.CharacterName;
		SlotData.GameTime = ((CurrentGameData->GameTime.Day * 48) - kStartHour) / 60;
		return SlotData;
	}
}

bool USaveManager::SaveData()
{
	if (CurrentGameData == nullptr) return false;

	UM3GameInstance::GetMapManager()->Save();
	if (UM3GameInstance::GetPC())
	{
		CurrentGameData->PlayerData.PlayerInfo = UM3GameInstance::GetPC()->GetPlayerInfo();
		CurrentGameData->PlayerData.CustomizingInformation = UM3GameInstance::GetPC()->CostomizingInformation;
		if (UM3GameInstance::GetPC()->EquipmentItem.WeaponItem) CurrentGameData->PlayerData.EquipmentData.WeaponItemID = UM3GameInstance::GetPC()->EquipmentItem.WeaponItem->DefaultInfo.ID;
		else CurrentGameData->PlayerData.EquipmentData.WeaponItemID = 0;
		if (UM3GameInstance::GetPC()->EquipmentItem.CapItem) CurrentGameData->PlayerData.EquipmentData.CapItemID = UM3GameInstance::GetPC()->EquipmentItem.CapItem->DefaultInfo.ID;
		else CurrentGameData->PlayerData.EquipmentData.CapItemID = 0;
		if (UM3GameInstance::GetPC()->EquipmentItem.TopItem) CurrentGameData->PlayerData.EquipmentData.TopItemID = UM3GameInstance::GetPC()->EquipmentItem.TopItem->DefaultInfo.ID;
		else CurrentGameData->PlayerData.EquipmentData.TopItemID = 0;
		if (UM3GameInstance::GetPC()->EquipmentItem.BottomItem) CurrentGameData->PlayerData.EquipmentData.BottomItemID = UM3GameInstance::GetPC()->EquipmentItem.BottomItem->DefaultInfo.ID;
		else CurrentGameData->PlayerData.EquipmentData.BottomItemID = 0;
		if (UM3GameInstance::GetPC()->EquipmentItem.HandsItem) CurrentGameData->PlayerData.EquipmentData.HandsItemID = UM3GameInstance::GetPC()->EquipmentItem.HandsItem->DefaultInfo.ID;
		else CurrentGameData->PlayerData.EquipmentData.HandsItemID = 0;
		if (UM3GameInstance::GetPC()->EquipmentItem.FeetItem) CurrentGameData->PlayerData.EquipmentData.FeetItemID = UM3GameInstance::GetPC()->EquipmentItem.FeetItem->DefaultInfo.ID;
		else CurrentGameData->PlayerData.EquipmentData.FeetItemID = 0;
	}
	CurrentGameData->PlayerData.InventoryData = UM3GameInstance::GetCharacterManager()->Inventory->GetBuildInventoryData();
	CurrentGameData->GameTime = UM3GameInstance::GetGameTimeManager()->GetGameTime();
	CurrentGameData->NPCData = UM3GameInstance::GetCharacterManager()->GetNPCData();
	CurrentGameData->PlayerData.QuestSwitchList = UM3GameInstance::GetQuestSystem()->GetSwitchList();
	return UGameplayStatics::SaveGameToSlot(CurrentGameData, CurrentGameData->SlotName, CurrentGameData->SlotIndex);
}

bool USaveManager::UnLoadData()
{
	CurrentGameData = nullptr;
	UM3GameInstance::GetMapManager()->Clear();
	UM3GameInstance::GetCharacterManager()->Clear();
	UM3GameInstance::GetActorManager()->Clear();
	UM3GameInstance::GetInstance()->bIsPlaying = false;
	IsLoad = false;
	return true;
}

bool USaveManager::LoadZoneData(int SlotIndex, FZoneData& Output, int PosX, int PosY)
{
	std::string Path;
	if (UE_EDITOR)
	{
		Path += "D:/M3Project";
	}
	else
	{
		Path += UHelper::GetClientPath();
	}
	Path += "/MapData/";
	if (SlotIndex != -1) Path += std::to_string(SlotIndex);
	Path += "l";
	Path += std::to_string(PosX << 16 | PosY);
	Path += ".dat";
	FILE* File = fopen(Path.c_str(), "rb");
	if (File == nullptr) return false;
	int Index = 0;
	for (int CubeX = 0; CubeX < kZoneSize; CubeX++)
	{
		for (int CubeY = 0; CubeY < kZoneSize; CubeY++)
		{
			for (int CubeZ = 0; CubeZ < kZoneSize; CubeZ++)
			{
				fscanf(File, "%c", &Output.CubeList[Index].CubeID);
				fscanf(File, "%c", &Output.CubeList[Index].Rotation);
				Index++;
			}
		}
	}
	fclose(File);
	return true;
}

bool USaveManager::SaveZoneData(int SlotIndex, FZoneData& input, int PosX, int PosY)
{
	std::string Path;
	if (UE_EDITOR)
	{
		Path += "D:/M3Project";
	}
	else
	{
		Path += UHelper::GetClientPath();
	}
	Path += "/MapData/";
	if (SlotIndex != -1) Path += std::to_string(SlotIndex);
	Path += "l";
	Path += std::to_string(PosX << 16 | PosY);
	Path += ".dat";
	FILE* File = fopen(Path.c_str(), "wb");
	if (File == nullptr) return false;
	int Index = 0;
	for (int CubeX = 0; CubeX < kZoneSize; CubeX++)
	{
		for (int CubeY = 0; CubeY < kZoneSize; CubeY++)
		{
			for (int CubeZ = 0; CubeZ < kZoneSize; CubeZ++)
			{
				fprintf(File, "%c", input.CubeList[Index].CubeID);
				fprintf(File, "%c", input.CubeList[Index].Rotation);
				Index++;
			}
		}
	}
	fclose(File);
	return true;
}

FPlayerData& USaveManager::GetPlayerData()
{
	check(CurrentGameData);
	return CurrentGameData->PlayerData;
}

FNPCData& USaveManager::GetNPCData()
{
	check(CurrentGameData);
	return CurrentGameData->NPCData;
}

FGameTime& USaveManager::GetGameTime()
{
	check(CurrentGameData);
	return CurrentGameData->GameTime;
}

void USaveManager::OpenGameLevel(FName LevelName)
{
	UM3GameInstance::GetMapManager()->CurrentLevelName = LevelName;
	UGameplayStatics::OpenLevel(UM3GameInstance::GetInstance()->GetWorld(), LevelName);
	CurrentGameData->LevelName = LevelName;
}

bool USaveManager::EditorMode()
{
	bIsEditorMode = true;
	USaveGame* GameData = UGameplayStatics::LoadGameFromSlot(FString("Defualt"), 0);
	CurrentGameData = Cast<USaveGameData>(GameData);
	if (CurrentGameData == nullptr) return false;
	IsLoad = true;
	CurrentGameData->PlayerData.PlayerInfo.PlayerLocation = FVector(10000.0f, 10000.0f, 1500.0f);
	CurrentGameData->GameTime.Hour = kStartHour;
	UM3GameInstance::GetGameTimeManager()->SetGameTime(CurrentGameData->GameTime);
	OpenGameLevel("DefualtLevel");
	UM3GameInstance::GetInstance()->bIsPlaying = true;
	return true;
}