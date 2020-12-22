#include "QuestSystem.h"
#include "ConstructorHelpers.h"
#include "Base/M3GameInstance.h"
#include "Resource/SaveData/SaveManager.h"
#include "LogicObject/Item/ItemManager.h"
#include "ModelCenter/Character/CharacterManager.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"

UQuestSystem::UQuestSystem()
{
	FString QuestDataPath = TEXT("DataTable'/Game/Resource/ResourceTable/QuestTable.QuestTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_Quest(*QuestDataPath);
	if (DT_Quest.Succeeded())
	{
		UDataTable* QuestTable = DT_Quest.Object;
		int Index = 0;
		while (true)
		{
			FQuestDataResource* DataResource = QuestTable->FindRow<FQuestDataResource>(FName(*(FString::FromInt(Index))), TEXT("z"));
			if (DataResource == nullptr) break;
			FQuestData Data;
			Data.QuestName = DataResource->QuestName;
			Data.Style = (EQuestStyle)DataResource->Style;
			TArray<FString> CompensationList;
			DataResource->Compensation.ParseIntoArray(CompensationList, TEXT("/"));
			for (int i = 0; i < CompensationList.Num(); i++)
			{
				FCompensationData CompensationData;
				TArray<FString> CompensationListSub;
				CompensationData.Type =	(EItemType)FCString::Atoi(*CompensationListSub[0]);
				CompensationData.Index = FCString::Atoi(*CompensationListSub[1]);
				CompensationData.Count = FCString::Atoi(*CompensationListSub[2]);
				Data.CompensationList.Add(CompensationData);
			}
			TArray<FString> AntecedentQuestList;
			DataResource->AntecedentQuestList.ParseIntoArray(AntecedentQuestList, TEXT("/"));
			for (int i = 0; i < AntecedentQuestList.Num(); i++)
			{
				Data.AntecedentQuestList.Add(FCString::Atoi(*AntecedentQuestList[i]));
			}
			BuildCondition(Data.Style, Data.ConditionList, DataResource->Condition);
			QuestDataList.Add(Data);
			Index++;
		}
	}
}

void UQuestSystem::BuildCondition(EQuestStyle Style, TArray<UConditionData*>& Array, FString Condition)
{
	TArray<FString> ConditionList;
	Condition.ParseIntoArray(ConditionList, TEXT("/"));
	for (int i = 0; i < ConditionList.Num(); i++)
	{
		TArray<FString> ConditionListSub;
		ConditionList[i].ParseIntoArray(ConditionListSub, TEXT(","));
		switch (Style)
		{
		case EQuestStyle::INSTANCE:
		{
			// Non Condition
		}break;
		case EQuestStyle::MONSTER_HUNTE:
		{
			UConditionData_MonsterHunte* Data = NewObject<UConditionData_MonsterHunte>();
			Data->Index = FCString::Atoi(*ConditionListSub[0]);
			Data->Count = FCString::Atoi(*ConditionListSub[1]);
			Array.Add(Data);
		}break;
		case EQuestStyle::SPOT_DISCOVER:
		{
			UConditionData_SpotDiscover* Data = NewObject<UConditionData_SpotDiscover>();
			Data->Pos = FVector(FCString::Atof(*ConditionListSub[0]), FCString::Atof(*ConditionListSub[1]), FCString::Atof(*ConditionListSub[2]));
			Data->length = FCString::Atof(*ConditionListSub[3]);
			Array.Add(Data);
		}break;
		case EQuestStyle::DELIVERY_ITEM:
		{
			UConditionData_DeliveryItem* Data = NewObject<UConditionData_DeliveryItem>();
			Data->Type = (EItemType)FCString::Atoi(*ConditionListSub[0]);
			Data->Index = FCString::Atoi(*ConditionListSub[1]);
			Data->Count = FCString::Atoi(*ConditionListSub[2]);
			Array.Add(Data);
		}break;
		case EQuestStyle::SHOW_ITEM:
		{
			UConditionData_ShowItem* Data = NewObject<UConditionData_ShowItem>();
			Data->Type = (EItemType)FCString::Atoi(*ConditionListSub[0]);
			Data->Index = FCString::Atoi(*ConditionListSub[1]);
			Array.Add(Data);
		}break;
		default:
			break;
		}
	}
}

void UQuestSystem::AddChecker(int Index)
{
	switch (QuestDataList[Index].Style)
	{
	case EQuestStyle::INSTANCE:
	{
		// Non Condition
	}break;
	case EQuestStyle::MONSTER_HUNTE:
	{
		for (int i = 0; i < QuestDataList[Index].ConditionList.Num(); i++)
		{
			UConditionData_MonsterHunte* Data = Cast<UConditionData_MonsterHunte>(QuestDataList[Index].ConditionList[i]);
			if (Data)
			{
				if (Checker_MonsterHunte.Find(Data->Index) == nullptr) Checker_MonsterHunte.Add(Data->Index, TArray<TTuple<int, int&>>());
				Checker_MonsterHunte[Data->Index].Add(TTuple<int, int&>(Data->Count, QuestSwitchList[Index].SubCount[i]));
			}
		}
	}break;
	case EQuestStyle::SPOT_DISCOVER:
	{
		for (int i = 0; i < QuestDataList[Index].ConditionList.Num(); i++)
		{
			UConditionData_SpotDiscover* Data = Cast<UConditionData_SpotDiscover>(QuestDataList[Index].ConditionList[i]);
			if (Data)
			{
				Checker_SpotDiscover.Add(TTuple<TTuple<float, FVector>, int&>(TTuple<float, FVector>(Data->length, Data->Pos), QuestSwitchList[Index].SubCount[i]));
			}
		}
	}break;
	case EQuestStyle::DELIVERY_ITEM:
	{
		for (int i = 0; i < QuestDataList[Index].ConditionList.Num(); i++)
		{
			UConditionData_DeliveryItem* Data = Cast<UConditionData_DeliveryItem>(QuestDataList[Index].ConditionList[i]);
			if (Data)
			{
				if (Checker_DeliveryItem.Find(Data->Type) == nullptr) Checker_DeliveryItem.Add(Data->Type, TMap<int, TArray<TTuple<int, int&>>>());
				if (Checker_DeliveryItem[Data->Type].Find(Data->Index) == nullptr) Checker_DeliveryItem[Data->Type].Add(Data->Index, TArray<TTuple<int, int&>>());
				Checker_DeliveryItem[Data->Type][Data->Index].Add(TTuple<int, int&>(Data->Count, QuestSwitchList[Index].SubCount[i]));
			}
		}
	}break;
	}
}

void UQuestSystem::RemoveChecker(int Index)
{
	switch (QuestDataList[Index].Style)
	{
	case EQuestStyle::INSTANCE:
	{
		// Non Condition
	}break;
	case EQuestStyle::MONSTER_HUNTE:
	{
		for (int i = 0; i < QuestDataList[Index].ConditionList.Num(); i++)
		{
			UConditionData_MonsterHunte* Data = Cast<UConditionData_MonsterHunte>(QuestDataList[Index].ConditionList[i]);
			for (int j = 0; j < Checker_MonsterHunte[Data->Index].Num(); j++)
			{
				int& Ref = Checker_MonsterHunte[Data->Index][j].Value;
				if (Ref == QuestSwitchList[Index].SubCount[i])
				{
					Checker_MonsterHunte[Data->Index].RemoveAt(j);
					break;
				}
			}
		}
	}break;
	case EQuestStyle::SPOT_DISCOVER:
	{
		for (int i = 0; i < QuestDataList[Index].ConditionList.Num(); i++)
		{
			UConditionData_SpotDiscover* Data = Cast<UConditionData_SpotDiscover>(QuestDataList[Index].ConditionList[i]);
			for (int j = 0; j < Checker_SpotDiscover.Num(); j++)
			{
				int& Ref = Checker_SpotDiscover[j].Value;
				if (Ref == QuestSwitchList[Index].SubCount[i])
				{
					Checker_SpotDiscover.RemoveAt(j);
				}
			}
		}
	}break;
	case EQuestStyle::DELIVERY_ITEM:
	{
		for (int i = 0; i < QuestDataList[Index].ConditionList.Num(); i++)
		{
			UConditionData_DeliveryItem* Data = Cast<UConditionData_DeliveryItem>(QuestDataList[Index].ConditionList[i]);
			for (int j = 0; j < Checker_DeliveryItem[Data->Type][Data->Index].Num(); j++)
			{
				int& Ref = Checker_DeliveryItem[Data->Type][Data->Index][j].Value;
				if (Ref == QuestSwitchList[Index].SubCount[i])
				{
					Checker_SpotDiscover.RemoveAt(j);
				}
			}
		}
	}break;
	}
}

void UQuestSystem::QuestActivate(int Index)
{
	QuestSwitchList[Index].State = EQuestState::ONGOING;
	QuestSwitchList[Index].SubCount.SetNum(QuestDataList[Index].ConditionList.Num());
	for (int i = 0; i < QuestSwitchList[Index].SubCount.Num(); i++) QuestSwitchList[Index].SubCount[i] = 0;
	AddChecker(Index);
}

void UQuestSystem::QuestComplete(int Index)
{
	QuestSwitchList[Index].State = EQuestState::COMPLETE;
	RemoveChecker(Index);
	for (int i = 0; i < QuestDataList.Num(); i++)
	{
		if (QuestSwitchList[i].State == EQuestState::DISABLE)
		{
			QuestSwitchList[i].State = EQuestState::STARTABLE;
			for (int j = 0; j < QuestDataList[i].AntecedentQuestList.Num(); j++)
			{
				if (QuestSwitchList[QuestDataList[i].AntecedentQuestList[j]].State != EQuestState::COMPLETE)
				{
					QuestSwitchList[i].State = EQuestState::DISABLE;
					break;
				}
			}
		}
	}
	QuestOriginalCompleteLogic((EQuestEnum)Index);
}

void UQuestSystem::KillMonster(int Index)
{
	if (Checker_MonsterHunte.Find(Index))
	{
		for (int i = 0; i < Checker_MonsterHunte[Index].Num(); i++)
		{
			Checker_MonsterHunte[Index][i].Value++;
		}
	}
}

void UQuestSystem::ModifyItemCount(EItemType Type, int Index, int Count)
{
	if (Checker_DeliveryItem.Find(Type))
	{
		if (Checker_DeliveryItem[Type].Find(Index))
		{
			for (int i = 0; i < Checker_DeliveryItem[Type][Index].Num(); i++)
			{
				Checker_DeliveryItem[Type][Index][i].Value = Count;
			}
		}
	}
}

void UQuestSystem::PositionCheck(FVector Position)
{
	for (int i = 0; i < Checker_SpotDiscover.Num(); i++)
	{
		if ((Checker_SpotDiscover[i].Key.Value - Position).Size() < Checker_SpotDiscover[i].Key.Key)
		{
			Checker_SpotDiscover[i].Value = true;
		}
	}
}

EQuestState UQuestSystem::GetQuestState(int Index)
{
	if (Index >= QuestSwitchList.Num()) return EQuestState::__NOT_VALUE__;
	return QuestSwitchList[Index].State;
}

void UQuestSystem::QuestOriginalCompleteLogic(EQuestEnum Enum)
{
	if (Enum == EQuestEnum::PROLOG)
	{
		UM3GameInstance::GetSaveManager()->GetPlayerData().PlayerInfo.PlayerLocation = FVector(19650.0f, 14450.0f, -1100.0f);
		UM3GameInstance::GetCharacterManager()->Inventory->AddItem(UM3GameInstance::GetItemManager()->GetWeaponItem(1001));
		UM3GameInstance::GetCharacterManager()->Inventory->AddItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(1001));
		UM3GameInstance::GetCharacterManager()->Inventory->AddItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(2001));
		UM3GameInstance::GetCharacterManager()->Inventory->AddItem(UM3GameInstance::GetItemManager()->GetEquipmentItem(4001));
		UM3GameInstance::GetSaveManager()->OpenGameLevel(FName("DefualtLevel"));
		return;
	}
}