#include "AnimationManager.h"
#include "ConstructorHelpers.h"

UAnimationManager::UAnimationManager(const FObjectInitializer& ObjectInitializer)
{
	FString AnimationTablePath = TEXT("DataTable'/Game/Resource/Character/Animation/AnimationTable.AnimationTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_ANI(*AnimationTablePath);
	if (DT_ANI.Succeeded())
	{
		UDataTable* AnimationTable = nullptr;
		AnimationTable = DT_ANI.Object;
		TMap<FName, uint8*> RowList = AnimationTable->GetRowMap();
		for (auto temp : RowList)
		{
			FString KeyName;
			temp.Key.AppendString(KeyName);
			FAnimationResourceTableRow* TableRow = (FAnimationResourceTableRow*)temp.Value;
			ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(*(TableRow->Resource));
			AnimationList.Add(KeyName, AnimBP.Class);
		}
	}

	AnimationTablePath = TEXT("DataTable'/Game/Resource/Character/Animation/AnimMontageTable.AnimMontageTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_ANIM(*AnimationTablePath);
	if (DT_ANIM.Succeeded())
	{
		UDataTable* AnimationTable = nullptr;
		AnimationTable = DT_ANIM.Object;
		TMap<FName, uint8*> RowList = AnimationTable->GetRowMap();
		for (auto temp : RowList)
		{
			FString KeyName;
			temp.Key.AppendString(KeyName);
			FAnimationResourceTableRow* TableRow = (FAnimationResourceTableRow*)temp.Value;
			ConstructorHelpers::FObjectFinder<UAnimMontage> AnimBP(*(TableRow->Resource));
			AnimMontageList.Add(KeyName, AnimBP.Object);
		}
	}
}

UClass* UAnimationManager::GetWeaponABP(EWeaponType type)
{
	FString KeyName;
	switch (type)
	{
	case EWeaponType::NONE:
		KeyName = "ABP_Defualt";
		break;
	case EWeaponType::TWOHANDED:
		KeyName = "ABP_Sword";
		break;
	default:
		break;
	}

	if (AnimationList.Find(KeyName) != nullptr)
	{
		return AnimationList[KeyName];
	}

	return nullptr;
}

UClass* UAnimationManager::GetMonsterABP(int index)
{
	FString KeyName = "ABP_Mop";
	KeyName.AppendInt(index);

	if (AnimationList.Find(KeyName) != nullptr)
	{
		return AnimationList[KeyName];
	}

	return nullptr;
}

UClass* UAnimationManager::GetBuildABP()
{
	FString KeyName = "ABP_Build";
	if (AnimationList.Find(KeyName) != nullptr)
	{
		return AnimationList[KeyName];
	}

	return nullptr;
}

UAnimMontage* UAnimationManager::GetReactMontage(EWeaponType type)
{
	FString KeyName;
	switch (type)
	{
	case EWeaponType::NONE:
		KeyName = "ANI_React";
		break;
	case EWeaponType::TWOHANDED:
		KeyName = "ANI_Sword_React";
		break;
	default:
		break;
	}

	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}

	return nullptr;
}

UAnimMontage* UAnimationManager::GetDownMontage(EWeaponType type)
{
	FString KeyName;
	switch (type)
	{
	case EWeaponType::NONE:
		KeyName = "ANI_Down";
		break;
	case EWeaponType::TWOHANDED:
		KeyName = "ANI_Sword_Down";
		break;
	default:
		break;
	}

	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}

	return nullptr;
}

UAnimMontage* UAnimationManager::GetWeaponAttackMontage(EWeaponType type, int Index)
{
	FString KeyName;
	switch (type)
	{
	case EWeaponType::TWOHANDED:
		KeyName = "ANI_Sword_Attack_";
		break;
	default:
		break;
	}

	if(Index < 10) 	KeyName.AppendInt(0);
	KeyName.AppendInt(Index);

	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}

	return nullptr;
}

UAnimMontage* UAnimationManager::GetWeaponChangeMontage(EWeaponType type, bool IsIn)
{
	FString KeyName;
	switch (type)
	{
	case EWeaponType::TWOHANDED:
		KeyName = "ANI_Sword_Change";
		break;
	default:
		break;
	}

	if (IsIn == false)
	{
		KeyName += FString("_Out");
	}

	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}

	return nullptr;
}

UAnimMontage* UAnimationManager::GetMonsterAttackMontage(int MonsterIndex)
{
	FString KeyName = "ANI_Mop";
	KeyName.AppendInt(MonsterIndex);
	KeyName += "_Attack";
	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}
	return nullptr;
}

UAnimMontage* UAnimationManager::GetMonsterReactMontage(int MonsterIndex, int SubIndex)
{
	FString KeyName = "ANI_Mop";
	KeyName.AppendInt(MonsterIndex);
	KeyName += "_React_";
	if (SubIndex < 10) KeyName.AppendInt(0);
	KeyName.AppendInt(SubIndex);

	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}
	return nullptr;
}

UAnimMontage* UAnimationManager::GetMonsterDeadMontage(int MonsterIndex, int SubIndex)
{
	FString KeyName = "ANI_Mop";
	KeyName.AppendInt(MonsterIndex);
	KeyName += "_Dead_";
	if (SubIndex < 10) KeyName.AppendInt(0);
	KeyName.AppendInt(SubIndex);

	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}
	return nullptr;
}

UAnimMontage* UAnimationManager::GetMonsterRunMontage(int MonsterIndex)
{
	FString KeyName = "ANI_Mop";
	KeyName.AppendInt(MonsterIndex);
	KeyName += "_Run";
	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}
	return nullptr;
}

UAnimMontage* UAnimationManager::GetBuildChangeMontage(bool IsIn)
{
	FString KeyName = (IsIn) ? "ANI_Build_Change_In" : "ANI_Build_Change_Out";
	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}
	return nullptr;
}

UAnimMontage* UAnimationManager::GetBuildOneMontage()
{
	FString KeyName = "ANI_Build_One";
	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}
	return nullptr;
}

UAnimMontage* UAnimationManager::GetBuildReactMontage()
{
	FString KeyName = "ANI_Build_React";
	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}
	return nullptr;
}

UAnimMontage* UAnimationManager::GetBuildDownMontage()
{
	FString KeyName = "ANI_Build_Down";
	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}
	return nullptr;
}

UAnimMontage* UAnimationManager::GetBuildHelperMontage()
{
	FString KeyName = "ANI_Build_Helper";
	if (AnimMontageList.Find(KeyName) != nullptr)
	{
		return AnimMontageList[KeyName];
	}
	return nullptr;
}