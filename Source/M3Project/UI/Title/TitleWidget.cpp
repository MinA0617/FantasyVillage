#include "TitleWidget.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/CharacterManager.h"
#include "Kismet/GameplayStatics.h"

void UTitleWidget::NativeConstruct()
{
	APlayerController* PCon = GetWorld()->GetFirstPlayerController<APlayerController>();
	if (PCon)
	{
		PCon->bShowMouseCursor = true;
		PCon->bEnableClickEvents = true;
		PCon->bEnableMouseOverEvents = true;
	}
}

void UTitleWidget::Exit()
{
	FGenericPlatformMisc::RequestExit(false);
}

bool UTitleWidget::CreateNewGame(int Index)
{
	return UM3GameInstance::GetSaveManager()->NewData(Index);
}

bool UTitleWidget::LoadGame(int Index)
{
	return UM3GameInstance::GetSaveManager()->LoadData(Index);
}

bool UTitleWidget::DeleteGame(int Index)
{
	return UM3GameInstance::GetSaveManager()->DeleteData(Index);
}

FGameSlotData UTitleWidget::GetSlotData(int Index)
{
	return UM3GameInstance::GetSaveManager()->GetSlotData(Index);
}


void UTitleWidget::EditorMode()
{
	UM3GameInstance::GetSaveManager()->EditorMode();
	//md-----
	int ID[] = { 101,102,103,104,105,106,107,108,109,110,10,11,12,13,14, };
	for (int i = 0; i < _countof(ID); i++)
	{
		UM3GameInstance::GetCharacterManager()->Inventory->
			AddItem(UM3GameInstance::GetItemManager()->GetInstallationItem(ID[i]), 456);
	}
	UM3GameInstance::GetCharacterManager()->Inventory->
		AddItem(UM3GameInstance::GetItemManager()->GetWeaponItem(1001));
	UM3GameInstance::GetCharacterManager()->Inventory->
		AddItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(1001));
	UM3GameInstance::GetCharacterManager()->Inventory->
		AddItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(2001));
	//UM3GameInstance::GetCharacterManager()->Inventory->
	//	AddItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(3001));
	UM3GameInstance::GetCharacterManager()->Inventory->
		AddItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(4001));
}

void UTitleWidget::NewEditData()
{
	UM3GameInstance::GetSaveManager()->NewEditData();
}