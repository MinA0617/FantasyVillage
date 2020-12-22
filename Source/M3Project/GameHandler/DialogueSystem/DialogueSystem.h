#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "DialogueSystem.generated.h"

UENUM()
enum class EDialogueStyle : uint8
{
	TEXT,					
	CHOICE_OPTION,			//C
	SEQUENCE,				//S
	BEGIN_QUEST,			//B
	QUEST_COMPLETE,			//Q
	__MAX__,
};

UCLASS()
class M3PROJECT_API UDialogue : public UObject
{
	GENERATED_BODY()
public:
	virtual EDialogueStyle GetStyle() { return EDialogueStyle::__MAX__; };
};

UCLASS()
class M3PROJECT_API UDialogue_Text : public UDialogue
{
	GENERATED_BODY()
public:
	virtual EDialogueStyle GetStyle() { return EDialogueStyle::TEXT; };
	FString Text;
};

UCLASS()
class M3PROJECT_API UDialogue_ChoiceOption : public UDialogue
{
	GENERATED_BODY()
public:
	virtual EDialogueStyle GetStyle() { return EDialogueStyle::CHOICE_OPTION; };
	struct ChoiceOption
	{
		FString ChoiceText;
		int32 JumpSection;
	};
	TArray<ChoiceOption> List;
};

UCLASS()
class M3PROJECT_API UDialogue_Sequence : public UDialogue
{
	GENERATED_BODY()
public:
	virtual EDialogueStyle GetStyle() { return EDialogueStyle::SEQUENCE; };
	FString Name;
};

UCLASS()
class M3PROJECT_API UDialogue_BeginQuest : public UDialogue
{
	GENERATED_BODY()
public:
	virtual EDialogueStyle GetStyle() { return EDialogueStyle::BEGIN_QUEST; };
	int Index;
};

UCLASS()
class M3PROJECT_API UDialogue_QuestComplete : public UDialogue
{
	GENERATED_BODY()
public:
	virtual EDialogueStyle GetStyle() { return EDialogueStyle::QUEST_COMPLETE; };
	int Index;
};

USTRUCT(BlueprintType)
struct FDialogueBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() FString Text;
};

USTRUCT(BlueprintType)
struct FDialogueSetBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() TArray<FDialogueBase> DialogueList;
};

USTRUCT(BlueprintType)
struct FDialogueSet
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() TArray<UDialogue*> DialogueList;
};

USTRUCT(BlueprintType)
struct FNPCDialogue
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() int QuestID;
	UPROPERTY() int DialogueID;
};

UCLASS()
class M3PROJECT_API UDialogueSystem : public UObject
{
	GENERATED_BODY()
public:
    UDialogueSystem();
public:
    TMap<int, FDialogueSetBase>		DialogueSetList;
	TMap<int, TArray<FNPCDialogue>> NPCDialogueList;
public:
    UFUNCTION() bool GetDialogueSet(FDialogueSet& DialogueSet, int Index);
	UFUNCTION() bool GetNPCDialogueSet(FDialogueSet& DialogueSet, int NPCIndex);
private:
	FDialogueSet ConvertBaseToDialogueSet(FDialogueSetBase& Base);
};

USTRUCT(BlueprintType)
struct FDialogueTableResource : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		int32 ParentsIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString Text;
};

USTRUCT(BlueprintType)
struct FNPCDialogueTableResource : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C_Info")
		FString DialogueList;
};