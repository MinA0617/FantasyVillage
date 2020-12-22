#include "CostomizeWidget.h"
#include "Components/TextBlock.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/Base/CostomizeManager.h"
#include "Resource/M3ResourceManager.h"
#include "ConstructorHelpers.h"

UCostomizeWidget::UCostomizeWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FString DataPath = TEXT("DataTable'/Game/Resource/ResourceTable/PalleteTable.PalleteTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_Pallete(*DataPath);
	if (DT_Pallete.Succeeded())
	{
		PalleteDataTable = DT_Pallete.Object;
	}
}

void UCostomizeWidget::NativeConstruct()
{
	TArray<FCostomizeColorPalleteResource*> List;
	PalleteDataTable->GetAllRows<FCostomizeColorPalleteResource>(TEXT("z"), List);
	for (int i = 0; i < List.Num(); i++)
	{
		if (List[i]->Type == EColorType::HairColor)
		{
			ColorPageList[(int)EColorType::HairColor]->AddColorItem(List[i]->Color);
			ColorPageList[(int)EColorType::EyeColor]->AddColorItem(List[i]->Color);
			ColorPageList[(int)EColorType::EyeborwColor]->AddColorItem(List[i]->Color);
		}
		else
		{
			ColorPageList[(int)List[i]->Type]->AddColorItem(List[i]->Color);
		}
	}

	LoadCount = 0;
	UM3ResourceManager* RM = UM3GameInstance::GetResourceManager();
	TArray<TArray<int>>& Array0 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::EYES);
	TArray<TArray<int>>& Array1 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::EYEBROW);
	TArray<TArray<int>>& Array2 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::MOUSE);
	TArray<TArray<int>>& Array3 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::EARS);
	TArray<TArray<int>>& Array4 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::NOSE);
	TArray<TArray<int>>& Array5 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::HEAD);
	TArray<TArray<int>>& Array6 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::HAIR);
	for (int i = 0; i < Array0.Num(); i++)	{
		for (int j = 0; j < Array0[i].Num(); j++)	{
			RM->GetAsyncObjectFromID(Array0[i][j], FStreamableDelegate::CreateUObject(this, &UCostomizeWidget::LoadingComplete));
			LoadCount++;	}	}
	for (int i = 0; i < Array1.Num(); i++)	{
		for (int j = 0; j < Array1[i].Num(); j++)	{
			RM->GetAsyncObjectFromID(Array1[i][j], FStreamableDelegate::CreateUObject(this, &UCostomizeWidget::LoadingComplete));
			LoadCount++;	}	}
	for (int i = 0; i < Array2.Num(); i++)	{
		for (int j = 0; j < Array2[i].Num(); j++)	{
			RM->GetAsyncObjectFromID(Array2[i][j], FStreamableDelegate::CreateUObject(this, &UCostomizeWidget::LoadingComplete));
			LoadCount++;	}	}
	for (int i = 0; i < Array3.Num(); i++)	{
		for (int j = 0; j < Array3[i].Num(); j++)	{
			RM->GetAsyncObjectFromID(Array3[i][j], FStreamableDelegate::CreateUObject(this, &UCostomizeWidget::LoadingComplete));
			LoadCount++;	}	}
	for (int i = 0; i < Array4.Num(); i++)	{
		for (int j = 0; j < Array4[i].Num(); j++)	{
			RM->GetAsyncObjectFromID(Array4[i][j], FStreamableDelegate::CreateUObject(this, &UCostomizeWidget::LoadingComplete));
			LoadCount++;	}	}
	for (int i = 0; i < Array5.Num(); i++)	{
		for (int j = 0; j < Array5[i].Num(); j++)	{
			RM->GetAsyncObjectFromID(Array5[i][j], FStreamableDelegate::CreateUObject(this, &UCostomizeWidget::LoadingComplete));
			LoadCount++;	}	}
	for (int i = 0; i < Array6.Num(); i++)	{
		for (int j = 0; j < Array6[i].Num(); j++)	{
			RM->GetAsyncObjectFromID(Array6[i][j], FStreamableDelegate::CreateUObject(this, &UCostomizeWidget::LoadingComplete));
			LoadCount++;
		}
	}
	IndexPageList[(int)EIndexType::EyeID]->SetMember(Array0.Num());
	IndexPageList[(int)EIndexType::EyebrowID]->SetMember(Array1.Num());
	IndexPageList[(int)EIndexType::MouseID]->SetMember(Array2.Num());
	IndexPageList[(int)EIndexType::EarsID]->SetMember(Array3.Num());
	IndexPageList[(int)EIndexType::NoseID]->SetMember(Array4.Num());
	IndexPageList[(int)EIndexType::HeadID]->SetMember(Array5.Num());
	IndexPageList[(int)EIndexType::HairID]->SetMember(Array6.Num());
}

void UCostomizeWidget::SetOwner(ACostomizeCharacter* owner)
{
	Owner = owner;
	FCustomizingInformation* CustomizingInformation = &(Owner->CostomizingInformation);

	for (int i = 0; i < ColorPageList[(int)EColorType::SkinColor]->ColorItemList.Num(); i++)
	{
		FColor& Color = ColorPageList[(int)EColorType::SkinColor]->ColorItemList[i]->Color;
		if (Color.R == CustomizingInformation->SkinColor.R &&
			Color.G == CustomizingInformation->SkinColor.G &&
			Color.B == CustomizingInformation->SkinColor.B)
		{
			ColorPageList[(int)EColorType::SkinColor]->SetFocus(i);
			break;
		}
	}
	for (int i = 0; i < ColorPageList[(int)EColorType::HairColor]->ColorItemList.Num(); i++)
	{
		FColor& Color = ColorPageList[(int)EColorType::HairColor]->ColorItemList[i]->Color;
		if (Color.R == CustomizingInformation->HairColor.R &&
			Color.G == CustomizingInformation->HairColor.G &&
			Color.B == CustomizingInformation->HairColor.B)
		{
			ColorPageList[(int)EColorType::HairColor]->SetFocus(i);
			break;
		}
	}
	for (int i = 0; i < ColorPageList[(int)EColorType::EyeColor]->ColorItemList.Num(); i++)
	{
		FColor& Color = ColorPageList[(int)EColorType::EyeColor]->ColorItemList[i]->Color;
		if (Color.R == CustomizingInformation->EyeColor.R &&
			Color.G == CustomizingInformation->EyeColor.G &&
			Color.B == CustomizingInformation->EyeColor.B)
		{
			ColorPageList[(int)EColorType::EyeColor]->SetFocus(i);
			break;
		}
	}
	for (int i = 0; i < ColorPageList[(int)EColorType::EyeborwColor]->ColorItemList.Num(); i++)
	{
		FColor& Color = ColorPageList[(int)EColorType::EyeborwColor]->ColorItemList[i]->Color;
		if (Color.R == CustomizingInformation->EyeborwColor.R &&
			Color.G == CustomizingInformation->EyeborwColor.G &&
			Color.B == CustomizingInformation->EyeborwColor.B)
		{
			ColorPageList[(int)EColorType::EyeborwColor]->SetFocus(i);
			break;
		}
	}
	for (int i = 0; i < ColorPageList[(int)EColorType::MouseColor]->ColorItemList.Num(); i++)
	{
		FColor& Color = ColorPageList[(int)EColorType::MouseColor]->ColorItemList[i]->Color;
		if (Color.R == CustomizingInformation->MouseColor.R &&
			Color.G == CustomizingInformation->MouseColor.G &&
			Color.B == CustomizingInformation->MouseColor.B)
		{
			ColorPageList[(int)EColorType::MouseColor]->SetFocus(i);
			break;
		}
	}

	IndexPageList[(int)EIndexType::HeadID	]->SetFocus(CustomizingInformation->HeadID);
	IndexPageList[(int)EIndexType::HairID	]->SetFocus(CustomizingInformation->HairID);
	IndexPageList[(int)EIndexType::EyeID	]->SetFocus(CustomizingInformation->EyeID);
	IndexPageList[(int)EIndexType::EyebrowID]->SetFocus(CustomizingInformation->EyebrowID);
	IndexPageList[(int)EIndexType::MouseID	]->SetFocus(CustomizingInformation->MouseID);
	IndexPageList[(int)EIndexType::NoseID	]->SetFocus(CustomizingInformation->NoseID);
	IndexPageList[(int)EIndexType::EarsID	]->SetFocus(CustomizingInformation->EarsID);

	SliderList[(int)EScalraType::EyeHeight		]->SetValue(CustomizingInformation->EyeHeight);
	SliderList[(int)EScalraType::EyeInterval	]->SetValue(CustomizingInformation->EyeInterval);
	SliderList[(int)EScalraType::EyeSize		]->SetValue(CustomizingInformation->EyeSize);
	SliderList[(int)EScalraType::EyeRoation		]->SetValue(CustomizingInformation->EyeRoation);
	SliderList[(int)EScalraType::EyeStretch		]->SetValue(CustomizingInformation->EyeStretch);
	SliderList[(int)EScalraType::EyebrowHeight	]->SetValue(CustomizingInformation->EyebrowHeight);
	SliderList[(int)EScalraType::EyebrowInterval]->SetValue(CustomizingInformation->EyebrowInterval);
	SliderList[(int)EScalraType::EyebrowSize	]->SetValue(CustomizingInformation->EyebrowSize);
	SliderList[(int)EScalraType::EyebrowRoation	]->SetValue(CustomizingInformation->EyebrowRoation);
	SliderList[(int)EScalraType::EyebrowStretch	]->SetValue(CustomizingInformation->EyebrowStretch);
	SliderList[(int)EScalraType::MouseHeight	]->SetValue(CustomizingInformation->MouseHeight);
	SliderList[(int)EScalraType::MouseSize		]->SetValue(CustomizingInformation->MouseSize);
	SliderList[(int)EScalraType::MouseStretch	]->SetValue(CustomizingInformation->MouseStretch);
	SliderList[(int)EScalraType::NoseHeight		]->SetValue(CustomizingInformation->NoseHeight);
	SliderList[(int)EScalraType::NoseSize		]->SetValue(CustomizingInformation->NoseSize);
	SliderList[(int)EScalraType::NoseStretch	]->SetValue(CustomizingInformation->NoseStretch);
};

void UCostomizeWidget::LoadingComplete()
{
	LoadCount--;
	if (LoadCount == 0)
	{
		UM3ResourceManager* RM = UM3GameInstance::GetResourceManager();
		TArray<TArray<int>>& Array0 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::EYES);
		TArray<TArray<int>>& Array1 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::EYEBROW);
		TArray<TArray<int>>& Array2 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::MOUSE);
		TArray<TArray<int>>& Array3 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::EARS);
		TArray<TArray<int>>& Array4 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::NOSE);
		TArray<TArray<int>>& Array5 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::HEAD);
		TArray<TArray<int>>& Array6 = UM3GameInstance::GetCostomizeManager()->GetCostomizeItemList(ECostomizeType::HAIR);
		for (int i = 0; i < Array0.Num(); i++)
		{
			UTexture* Tex = RM->GetObjectFromID< UTexture>(Array0[i][0]);
			IndexPageList[(int)EIndexType::EyeID]->IndexItemList[i]->SetTextrue(Tex);
			Tex = RM->GetObjectFromID< UTexture>(Array0[i][1]);
			IndexPageList[(int)EIndexType::EyeID]->IndexItemList[i]->SetTextrue_Sub(Tex);
		}
		for (int i = 0; i < Array1.Num(); i++)
		{
			UTexture* Tex = RM->GetObjectFromID< UTexture>(Array1[i][0]);
			IndexPageList[(int)EIndexType::EyebrowID]->IndexItemList[i]->SetTextrue(Tex);
		}
		for (int i = 0; i < Array2.Num(); i++)
		{
			UTexture* Tex = RM->GetObjectFromID< UTexture>(Array2[i][0]);
			IndexPageList[(int)EIndexType::MouseID]->IndexItemList[i]->SetTextrue(Tex);
		}
		for (int i = 0; i < Array3.Num(); i++)
		{
			UTexture* Tex = RM->GetObjectFromID< UTexture>(Array3[i][0]);
			IndexPageList[(int)EIndexType::EarsID]->IndexItemList[i]->SetTextrue(Tex);
		}
		for (int i = 0; i < Array4.Num(); i++)
		{
			UTexture* Tex = RM->GetObjectFromID< UTexture>(Array4[i][0]);
			IndexPageList[(int)EIndexType::NoseID]->IndexItemList[i]->SetTextrue(Tex);
		}
		for (int i = 0; i < Array5.Num(); i++)
		{
			UTexture* Tex = RM->GetObjectFromID< UTexture>(Array5[i][0]);
			IndexPageList[(int)EIndexType::HeadID]->IndexItemList[i]->SetTextrue(Tex);
		}
		for (int i = 0; i < Array6.Num(); i++)
		{
			UTexture* Tex = RM->GetObjectFromID< UTexture>(Array6[i][0]);
			IndexPageList[(int)EIndexType::HairID]->IndexItemList[i]->SetTextrue(Tex);
		}
	}
}

void UCostomizeWidget::ModifyColorParma(EColorType Type, FColor Color)
{
	switch (Type)
	{
	case EColorType::SkinColor:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeColorValue(Owner, ECostomizeParts::SkinColor, Color);
		break;
	case EColorType::HairColor:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeColorValue(Owner, ECostomizeParts::HairColor, Color);
		break;
	case EColorType::EyeColor:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeColorValue(Owner, ECostomizeParts::EyeColor, Color);
		break;
	case EColorType::EyeborwColor:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeColorValue(Owner, ECostomizeParts::EyeborwColor, Color);
		break;
	case EColorType::MouseColor:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeColorValue(Owner, ECostomizeParts::MouseColor, Color);
		break;
	default:
		break;
	}
}

void UCostomizeWidget::ModifyIndexParma(EIndexType Type, int Index)
{
	switch (Type)
	{
	case EIndexType::HeadID:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeTextureValue(Owner, ECostomizeParts::HeadID, Index);
		break;
	case EIndexType::HairID:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeTextureValue(Owner, ECostomizeParts::HairID, Index);
		break;
	case EIndexType::EyeID:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeTextureValue(Owner, ECostomizeParts::EyeID, Index);
		break;
	case EIndexType::EyebrowID:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeTextureValue(Owner, ECostomizeParts::EyebrowID, Index);
		break;
	case EIndexType::MouseID:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeTextureValue(Owner, ECostomizeParts::MouseID, Index);
		break;
	case EIndexType::NoseID:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeTextureValue(Owner, ECostomizeParts::NoseID, Index);
		break;
	case EIndexType::EarsID:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeTextureValue(Owner, ECostomizeParts::EarsID, Index);
		break;
	default:
		break;
	}
}

void UCostomizeWidget::ModifyScalarParma(EScalraType Type, float Value)
{
	switch (Type)
	{
	case EScalraType::EyeHeight:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::EyeHeight, Value);
		break;
	case EScalraType::EyeInterval:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::EyeInterval, Value);
		break;
	case EScalraType::EyeSize:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::EyeSize, Value);
		break;
	case EScalraType::EyeRoation:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::EyeRoation, Value);
		break;
	case EScalraType::EyeStretch:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::EyeStretch, Value);
		break;
	case EScalraType::EyebrowHeight:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::EyebrowHeight, Value);
		break;
	case EScalraType::EyebrowInterval:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::EyebrowInterval, Value);
		break;
	case EScalraType::EyebrowSize:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::EyebrowSize, Value);
		break;
	case EScalraType::EyebrowRoation:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::EyebrowRoation, Value);
		break;
	case EScalraType::EyebrowStretch:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::EyebrowStretch, Value);
		break;
	case EScalraType::MouseHeight:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::MouseHeight, Value);
		break;
	case EScalraType::MouseSize:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::MouseSize, Value);
		break;
	case EScalraType::MouseStretch:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::MouseStretch, Value);
		break;
	case EScalraType::NoseHeight:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::NoseHeight, Value);
		break;
	case EScalraType::NoseSize:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::NoseSize, Value);
		break;
	case EScalraType::NoseStretch:
		UM3GameInstance::GetCostomizeManager()->ModifyCostomizeScalaValue(Owner, ECostomizeParts::NoseStretch, Value);
		break;
	default:
		break;
	}

}

void UCostomizeWidget::ModifySex(bool IsFemale)
{
	UM3GameInstance::GetCostomizeManager()->ModifyCostomizeSex(Owner, IsFemale);
	if (IsFemale)
	{
		MaleBox->SetCheckedState(ECheckBoxState::Unchecked);
		FemaleBox->SetCheckedState(ECheckBoxState::Checked);
	}
	else
	{
		FemaleBox->SetCheckedState(ECheckBoxState::Unchecked);
		MaleBox->SetCheckedState(ECheckBoxState::Checked);
	}
}