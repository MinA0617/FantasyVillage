#include "DialogueSystem.h"
#include "ConstructorHelpers.h"
#include "Base/M3GameInstance.h"
#include "GameHandler/QuestSystem/QuestSystem.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"

UDialogueSystem::UDialogueSystem()
{
	FString DialogueDataPath = TEXT("DataTable'/Game/Resource/ResourceTable/DialogueTable.DialogueTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_Dialogue(*DialogueDataPath);
	UDataTable* DataTable = nullptr;
	if (DT_Dialogue.Succeeded()) DataTable = DT_Dialogue.Object;

	if (DataTable)
	{
		TArray<FDialogueTableResource*> List;
		DataTable->GetAllRows<FDialogueTableResource>(TEXT("z"), List);
		for (int i = 0; i < List.Num(); i++)
		{
			FDialogueSetBase* DialogueSet = DialogueSetList.Find(List[i]->ParentsIndex);
			if (DialogueSet == nullptr)
			{
				DialogueSetList.Add(List[i]->ParentsIndex, FDialogueSetBase());
			}
			FDialogueBase NewDialogue;
			NewDialogue.Text = List[i]->Text;
			DialogueSetList[List[i]->ParentsIndex].DialogueList.Add(NewDialogue);
		}
	}

	FString NPCDialoguePath = TEXT("DataTable'/Game/Resource/ResourceTable/NPCDialogueTable.NPCDialogueTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_NPCDialogue(*NPCDialoguePath);
	UDataTable* NPCDataTable = nullptr;
	if (DT_NPCDialogue.Succeeded()) NPCDataTable = DT_NPCDialogue.Object;
	if (NPCDataTable)
	{
		TMap<FName, uint8*> RowList = NPCDataTable->GetRowMap();
		for (auto temp : RowList)
		{
			FString KeyString;
			temp.Key.AppendString(KeyString);
			int Key = FCString::Atoi(*KeyString);
			FNPCDialogueTableResource* TableRow = (FNPCDialogueTableResource*)temp.Value;
			NPCDialogueList.Add(Key, TArray<FNPCDialogue>());
			TArray<FString> StringList;
			TableRow->DialogueList.ParseIntoArray(StringList, TEXT("/"));
			FNPCDialogue Dialogue;
			Dialogue.QuestID = -1;
			Dialogue.DialogueID = FCString::Atoi(*StringList[0]);
			NPCDialogueList[Key].Add(Dialogue);
			for (int j = 1; j < StringList.Num();)
			{
				FNPCDialogue NewDialogue;
				NewDialogue.QuestID = FCString::Atoi(*StringList[j++]);
				NewDialogue.DialogueID = FCString::Atoi(*StringList[j++]);
				NPCDialogueList[Key].Add(NewDialogue);
			}
		}
	}
}

bool UDialogueSystem::GetDialogueSet(FDialogueSet& DialogueSet, int Index)
{
	FDialogueSetBase* Dialogue = DialogueSetList.Find(Index);
	if (Dialogue)
	{
		DialogueSet = ConvertBaseToDialogueSet(*Dialogue);
		return true;
	}
	return false;
}

bool UDialogueSystem::GetNPCDialogueSet(FDialogueSet& DialogueSet, int NPCIndex)
{
	TArray<FNPCDialogue>* NPCDialogue = NPCDialogueList.Find(NPCIndex);
	if (NPCDialogue)
	{
		int CurrentDialogueID = (*NPCDialogue)[0].DialogueID;
		int Index = 1;
		while (true)
		{
			if (Index >= (*NPCDialogue).Num()) break;
			if (UM3GameInstance::GetQuestSystem()->GetQuestState((*NPCDialogue)[Index].QuestID) == EQuestState::COMPLETE)
			{
				CurrentDialogueID = (*NPCDialogue)[Index].DialogueID;
				Index++;
				continue;
			}
			break;
		}
		return GetDialogueSet(DialogueSet, CurrentDialogueID);
	}
	return false;
}

FDialogueSet UDialogueSystem::ConvertBaseToDialogueSet(FDialogueSetBase& Base)
{
	FDialogueSet NewSet;
	for (int i = 0; i < Base.DialogueList.Num(); i++)
	{
		switch (Base.DialogueList[i].Text[0])
		{
		case 'C':
		{
			UDialogue_ChoiceOption* Dialogue = NewObject<UDialogue_ChoiceOption>();
			FString Text;
			Text.AppendChars(&(Base.DialogueList[i].Text[1]), Base.DialogueList[i].Text.Len() - 1);
			TArray<FString> Parser;
			Text.ParseIntoArray(Parser, TEXT("/"));
			for (int j = 0; j < Parser.Num();)
			{
				UDialogue_ChoiceOption::ChoiceOption NewOption;
				NewOption.ChoiceText = Parser[j];
				NewOption.JumpSection = FCString::Atoi(*Parser[j + 1]);
				Dialogue->List.Add(NewOption);
				j += 2;
			}
			NewSet.DialogueList.Add(Dialogue);
		}
		break;
		case 'S':
		{
			UDialogue_Sequence* Dialogue = NewObject<UDialogue_Sequence>();
			Dialogue->Name.AppendChars(&(Base.DialogueList[i].Text[1]), Base.DialogueList[i].Text.Len() - 1);
			NewSet.DialogueList.Add(Dialogue);
		}
		break;
		case 'B':
		{
			UDialogue_BeginQuest* Dialogue = NewObject<UDialogue_BeginQuest>();
			FString Text;
			Text.AppendChars(&(Base.DialogueList[i].Text[1]), Base.DialogueList[i].Text.Len() - 1);
			Dialogue->Index = FCString::Atoi(*Text);
			NewSet.DialogueList.Add(Dialogue);
		}
		break;
		case 'Q':
		{
			UDialogue_QuestComplete* Dialogue = NewObject<UDialogue_QuestComplete>();
			FString Text;
			Text.AppendChars(&(Base.DialogueList[i].Text[1]), Base.DialogueList[i].Text.Len() - 1);
			Dialogue->Index = FCString::Atoi(*Text);
			NewSet.DialogueList.Add(Dialogue);
		}
		break;
		default:
		{
			UDialogue_Text* Dialogue = NewObject<UDialogue_Text>();
			for (int j = 0; j < Base.DialogueList[i].Text.Len(); j++)
			{
				if (Base.DialogueList[i].Text[j] == '#')
				{
					j++;
					switch (Base.DialogueList[i].Text[j])
					{
					case 'N':
					{
						FString CN = UM3GameInstance::GetPC()->GetPlayerInfo().CharacterName.ToString();
						Dialogue->Text.AppendChars(*CN, CN.Len());
					}
					default:
						break;
					}
				}
				else
				{
					Dialogue->Text.AppendChar(Base.DialogueList[i].Text[j]);
				}
			}
			NewSet.DialogueList.Add(Dialogue);
		}
		break;
		}
	}
	return NewSet;
}