#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "LogicObject/Item/ItemManager.h"
#include "QuestSystem.generated.h"

UENUM()
enum class EQuestState : uint8
{
	DISABLE,
	STARTABLE,
	ONGOING,
	COMPLETE,
	__NOT_VALUE__,
};

UENUM()
enum class EQuestStyle : uint8
{
	INSTANCE,
	MONSTER_HUNTE,
	SPOT_DISCOVER,
	DELIVERY_ITEM,
	SHOW_ITEM,
	__MAX__,
};

enum class EQuestEnum : uint8
{
	PROLOG,
	__MAX__,
};

USTRUCT(BlueprintType)
struct FQuestState
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY() EQuestState State;
	UPROPERTY() TArray<int> SubCount;
};

UCLASS()
class M3PROJECT_API UConditionData : public UObject
{
	GENERATED_BODY()
public:
};

UCLASS()
class M3PROJECT_API UConditionData_MonsterHunte : public UConditionData
{
	GENERATED_BODY()
public:
	int			Index;
	int			Count;
};

UCLASS()
class M3PROJECT_API UConditionData_SpotDiscover : public UConditionData
{
	GENERATED_BODY()
public:
	FVector		Pos;
	float		length;
};

UCLASS()
class M3PROJECT_API UConditionData_DeliveryItem : public UConditionData
{
	GENERATED_BODY()
public:
	EItemType	Type;
	int			Index;
	int			Count;
};

UCLASS()
class M3PROJECT_API UConditionData_ShowItem : public UConditionData
{
	GENERATED_BODY()
public:
	EItemType	Type;
	int			Index;
};

struct FCompensationData
{
public:
	EItemType	Type;
	int			Index;
	int			Count;
};

struct FQuestData
{
public:
	FString						QuestName;
	EQuestStyle					Style;
	uint32						CompensationGold;
	TArray<FCompensationData>	CompensationList;
	TArray<UConditionData*>		ConditionList;
	TArray<int>					AntecedentQuestList;
};

USTRUCT(BlueprintType)
struct FQuestDataResource : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info") FString		QuestName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info") EQuestStyle	Style;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info") int32		CompensationGold;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info") FString		Compensation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info") FString		Condition;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Info") FString		AntecedentQuestList;
};

UCLASS()
class M3PROJECT_API UQuestSystem : public UObject
{
	GENERATED_BODY()
public:
	UQuestSystem();
private:
	void BuildCondition(EQuestStyle Style, TArray<UConditionData*>& Array, FString Condition);
	void AddChecker(int Index);
	void RemoveChecker(int Index);
	void QuestOriginalCompleteLogic(EQuestEnum Enum);
private:
	TArray<FQuestData>										QuestDataList;
	TArray<FQuestState>										QuestSwitchList;
	TMap<int, TArray<TTuple<int, int&>>>					Checker_MonsterHunte;
	TArray<TTuple<TTuple<float, FVector>, int&>>			Checker_SpotDiscover;
	TMap<EItemType, TMap<int, TArray<TTuple<int, int&>>>>	Checker_DeliveryItem;
public:
	TArray<FQuestState>& GetSwitchList() { return QuestSwitchList;	};
	void SetSwitchList(TArray<FQuestState>& QuestSwitch) { QuestSwitchList = QuestSwitch; };
	void KillMonster(int Index);
	void ModifyItemCount(EItemType Type, int Index, int Count);
	void PositionCheck(FVector Position);
	EQuestState GetQuestState(int Index);
public:
	void QuestActivate(int Index);
	void QuestComplete(int Index);
};