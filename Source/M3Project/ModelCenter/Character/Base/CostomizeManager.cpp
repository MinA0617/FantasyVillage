#include "CostomizeManager.h"
#include "Base/M3GameInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ConstructorHelpers.h"
#include "ModelCenter/Character/Base/CostomizeCharacter.h"
#include "Engine/StaticMesh.h"

const int kFaceMaterialID = 30000001;
const int kHairMaterialID = 30000002;
const int kBodyMaterialID = 30000003;

UCostomizeManager::UCostomizeManager()
{
	FString CostomizeItemTablePath = TEXT("DataTable'/Game/Resource/ResourceTable/CostomizeItemTable.CostomizeItemTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_COST(*CostomizeItemTablePath);
	if (DT_COST.Succeeded())
	{
		CostomizeItemList.SetNum(7);
		UDataTable* CostomizeItemTable = DT_COST.Object;
		TMap<FName, uint8*> RowList = CostomizeItemTable->GetRowMap();
		for (auto temp : RowList)
		{
			FString KeyName;
			temp.Key.AppendString(KeyName);
			FCostomizeItemResource* TableRow = (FCostomizeItemResource*)temp.Value;
			TArray<int> NewArray;
			NewArray.Add(TableRow->ResourceIconID);
			if (TableRow->ResourceMeshID) NewArray.Add(TableRow->ResourceMeshID);
			if (TableRow->ResourceSubID) NewArray.Add(TableRow->ResourceSubID);
			CostomizeItemList[(int)TableRow->Type].Add(NewArray);
		}
	}
}

void UCostomizeManager::Init()
{
	MinMaxList[(int)ECostomizeParts::EyebrowHeight	] = FValueMinMax(-100.0f, 100.0f);
	MinMaxList[(int)ECostomizeParts::EyebrowInterval] = FValueMinMax(40.0f, 120.0f);
	MinMaxList[(int)ECostomizeParts::EyebrowSize	] = FValueMinMax(0.05f, 0.15f);
	MinMaxList[(int)ECostomizeParts::EyebrowRoation	] = FValueMinMax(-0.15f, 0.15f);
	MinMaxList[(int)ECostomizeParts::EyebrowStretch	] = FValueMinMax(0.05f, 0.15f);
	MinMaxList[(int)ECostomizeParts::EyeHeight		] = FValueMinMax(-120.0f, 0.0f);
	MinMaxList[(int)ECostomizeParts::EyeInterval	] = FValueMinMax(20.0f, 140.0f);
	MinMaxList[(int)ECostomizeParts::EyeSize		] = FValueMinMax(0.05f, 0.15f);
	MinMaxList[(int)ECostomizeParts::EyeRoation		] = FValueMinMax(-0.15f,0.15f);
	MinMaxList[(int)ECostomizeParts::EyeStretch		] = FValueMinMax(0.05f, 0.15f);
	MinMaxList[(int)ECostomizeParts::MouseHeight	] = FValueMinMax(-80.0f, 80.0f);
	MinMaxList[(int)ECostomizeParts::MouseSize		] = FValueMinMax(0.05f, 0.15f);
	MinMaxList[(int)ECostomizeParts::MouseStretch	] = FValueMinMax(0.05f, 0.15f);
	MinMaxList[(int)ECostomizeParts::NoseHeight		] = FValueMinMax(-14.0f, 10.0f);
	MinMaxList[(int)ECostomizeParts::NoseSize		] = FValueMinMax(0.5f, 1.5f);
	MinMaxList[(int)ECostomizeParts::NoseStretch	] = FValueMinMax(0.5f, 1.5f);
}

void UCostomizeManager::SetCostomize(ACostomizeCharacter* owner)
{
	owner->SetupSex(owner->CostomizingInformation.IsFemale);

	int HeadID		= (CostomizeItemList[(int)ECostomizeType::HEAD].Num() <= owner->CostomizingInformation.HeadID) ? 0 : CostomizeItemList[(int)ECostomizeType::HEAD][owner->CostomizingInformation.HeadID][1];
	int HairID		= (CostomizeItemList[(int)ECostomizeType::HAIR].Num() <= owner->CostomizingInformation.HairID) ? 0 : CostomizeItemList[(int)ECostomizeType::HAIR][owner->CostomizingInformation.HairID][1];
	int EarsID		= (CostomizeItemList[(int)ECostomizeType::EARS].Num() <= owner->CostomizingInformation.EarsID) ? 0 : CostomizeItemList[(int)ECostomizeType::EARS][owner->CostomizingInformation.EarsID][1];
	int NoseID		= (CostomizeItemList[(int)ECostomizeType::NOSE].Num() <= owner->CostomizingInformation.NoseID) ? 0 : CostomizeItemList[(int)ECostomizeType::NOSE][owner->CostomizingInformation.NoseID][1];
	int EyesID		= (CostomizeItemList[(int)ECostomizeType::EYES].Num() <= owner->CostomizingInformation.EyeID) ? 0 : CostomizeItemList[(int)ECostomizeType::EYES][owner->CostomizingInformation.EyeID][0];
	int PupilID		= (CostomizeItemList[(int)ECostomizeType::EYES].Num() <= owner->CostomizingInformation.EyeID) ? 0 : CostomizeItemList[(int)ECostomizeType::EYES][owner->CostomizingInformation.EyeID][1];
	int EyeBrowsID	= (CostomizeItemList[(int)ECostomizeType::EYEBROW].Num() <= owner->CostomizingInformation.EyebrowID) ? 0 : CostomizeItemList[(int)ECostomizeType::EYEBROW][owner->CostomizingInformation.EyebrowID][0];
	int MouseID		= (CostomizeItemList[(int)ECostomizeType::MOUSE].Num() <= owner->CostomizingInformation.MouseID) ? 0 : CostomizeItemList[(int)ECostomizeType::MOUSE][owner->CostomizingInformation.MouseID][0];

	UStaticMesh* HeadMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(HeadID);
	UStaticMesh* HairMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(HairID);
	UStaticMesh* EarsMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(EarsID);
	UStaticMesh* NoseMesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(NoseID);
	owner->CharacterPartsComponent.HeadComponent->SetStaticMesh(HeadMesh);
	owner->CharacterPartsComponent.NoseComponent->SetStaticMesh(NoseMesh);
	owner->CharacterPartsComponent.EarsComponent->SetStaticMesh(EarsMesh);
	owner->CharacterPartsComponent.HairComponent->SetStaticMesh(HairMesh);

	UMaterial* HairMat = UM3GameInstance::GetResourceManager()->GetObjectFromID<UMaterial>(kHairMaterialID);
	UMaterialInstanceDynamic* HairMatInst = UMaterialInstanceDynamic::Create(HairMat, this);
	check(HairMatInst != nullptr);
	owner->CharacterPartsComponent.HairComponent->SetMaterial(0, HairMatInst);

	UMaterial* FaceMat = UM3GameInstance::GetResourceManager()->GetObjectFromID<UMaterial>(kFaceMaterialID);
	UMaterialInstanceDynamic* FaceMatInst = UMaterialInstanceDynamic::Create(FaceMat, this);
	check(FaceMatInst != nullptr);
	owner->CharacterPartsComponent.HeadComponent->SetMaterial(0, FaceMatInst);

	UMaterial* BodyMat = UM3GameInstance::GetResourceManager()->GetObjectFromID<UMaterial>(kBodyMaterialID);
	UMaterialInstanceDynamic* BodyMatInst = UMaterialInstanceDynamic::Create(BodyMat, this);
	check(BodyMatInst != nullptr);
	owner->CharacterPartsComponent.TopComponent->SetMaterialByName("Skin", BodyMatInst);
	owner->CharacterPartsComponent.BottomComponent->SetMaterialByName("Skin", BodyMatInst);
	owner->CharacterPartsComponent.HandsComponent->SetMaterialByName("Skin", BodyMatInst);
	owner->CharacterPartsComponent.FeetComponent->SetMaterialByName("Skin", BodyMatInst);
	owner->CharacterPartsComponent.NoseComponent->SetMaterialByName("Skin", BodyMatInst);
	owner->CharacterPartsComponent.EarsComponent->SetMaterialByName("Skin", BodyMatInst);

	FaceMatInst->SetScalarParameterValue("EyeHeight",		ConvertValue(ECostomizeParts::EyeHeight, owner->CostomizingInformation.EyeHeight));
	FaceMatInst->SetScalarParameterValue("EyeInterval",		ConvertValue(ECostomizeParts::EyeInterval, owner->CostomizingInformation.EyeInterval));
	FaceMatInst->SetScalarParameterValue("EyeSize",			ConvertValue(ECostomizeParts::EyeSize, owner->CostomizingInformation.EyeSize));
	FaceMatInst->SetScalarParameterValue("EyeRoation",		ConvertValue(ECostomizeParts::EyeRoation, owner->CostomizingInformation.EyeRoation));
	FaceMatInst->SetScalarParameterValue("EyeStretch",		ConvertValue(ECostomizeParts::EyeStretch, owner->CostomizingInformation.EyeStretch));
	FaceMatInst->SetScalarParameterValue("EyebrowHeight",	ConvertValue(ECostomizeParts::EyebrowHeight, owner->CostomizingInformation.EyebrowHeight));
	FaceMatInst->SetScalarParameterValue("EyebrowInterval", ConvertValue(ECostomizeParts::EyebrowInterval, owner->CostomizingInformation.EyebrowInterval));
	FaceMatInst->SetScalarParameterValue("EyebrowSize",		ConvertValue(ECostomizeParts::EyebrowSize, owner->CostomizingInformation.EyebrowSize));
	FaceMatInst->SetScalarParameterValue("EyebrowRoation",	ConvertValue(ECostomizeParts::EyebrowRoation, owner->CostomizingInformation.EyebrowRoation));
	FaceMatInst->SetScalarParameterValue("EyebrowStretch",	ConvertValue(ECostomizeParts::EyebrowStretch, owner->CostomizingInformation.EyebrowStretch));
	FaceMatInst->SetScalarParameterValue("MouseHeight",		ConvertValue(ECostomizeParts::MouseHeight, owner->CostomizingInformation.MouseHeight));
	FaceMatInst->SetScalarParameterValue("MouseSize",		ConvertValue(ECostomizeParts::MouseSize, owner->CostomizingInformation.MouseSize));
	FaceMatInst->SetScalarParameterValue("MouseStretch",	ConvertValue(ECostomizeParts::MouseStretch, owner->CostomizingInformation.MouseStretch));

	FaceMatInst->SetVectorParameterValue("SkinColor", owner->CostomizingInformation.SkinColor);
	FaceMatInst->SetVectorParameterValue("EyeborwColor", owner->CostomizingInformation.EyeborwColor);
	FaceMatInst->SetVectorParameterValue("EyeColor", owner->CostomizingInformation.EyeColor);
	FaceMatInst->SetVectorParameterValue("MouseColor", owner->CostomizingInformation.MouseColor);

	UTexture* EyeBrows = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture>(EyeBrowsID);
	UTexture* Eyes = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture>(EyesID);
	UTexture* Mouse = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture>(MouseID);
	UTexture* Pupil = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture>(PupilID);

	FaceMatInst->SetTextureParameterValue("EyeBrows", EyeBrows);
	FaceMatInst->SetTextureParameterValue("Eyes", Eyes);
	FaceMatInst->SetTextureParameterValue("Mouse", Mouse);
	FaceMatInst->SetTextureParameterValue("Pupil", Pupil);
	
	BodyMatInst->SetVectorParameterValue("SkinColor", owner->CostomizingInformation.SkinColor);
	HairMatInst->SetVectorParameterValue("HairColor", owner->CostomizingInformation.HairColor);

	owner->CharacterPartsComponent.NoseComponent->SetRelativeLocation(FVector(.0f, .0f, ConvertValue(ECostomizeParts::NoseHeight, owner->CostomizingInformation.NoseHeight)));
	owner->CharacterPartsComponent.NoseComponent->SetRelativeScale3D(FVector(ConvertValue(ECostomizeParts::NoseStretch, owner->CostomizingInformation.NoseStretch), .0f, ConvertValue(ECostomizeParts::NoseSize, owner->CostomizingInformation.NoseSize)));
}

void UCostomizeManager::ModifyCostomizeScalaValue(ACostomizeCharacter* owner, ECostomizeParts name, float value)
{
	UMaterialInstanceDynamic* FaceMatInst = Cast<UMaterialInstanceDynamic>(owner->CharacterPartsComponent.HeadComponent->GetMaterial(0));

	switch (name)
	{
	case ECostomizeParts::EyebrowHeight:
		owner->CostomizingInformation.EyebrowHeight = value;
		FaceMatInst->SetScalarParameterValue("EyebrowHeight", ConvertValue(name, value));
		break;
	case ECostomizeParts::EyebrowInterval:
		owner->CostomizingInformation.EyebrowInterval = value;
		FaceMatInst->SetScalarParameterValue("EyebrowInterval", ConvertValue(name, value));
		break;
	case ECostomizeParts::EyebrowSize:
		owner->CostomizingInformation.EyebrowSize = value;
		FaceMatInst->SetScalarParameterValue("EyebrowSize", ConvertValue(name, value));
		break;
	case ECostomizeParts::EyebrowRoation:
		owner->CostomizingInformation.EyebrowRoation = value;
		FaceMatInst->SetScalarParameterValue("EyebrowRoation", ConvertValue(name, value));
		break;
	case ECostomizeParts::EyebrowStretch:
		owner->CostomizingInformation.EyebrowStretch = value;
		FaceMatInst->SetScalarParameterValue("EyebrowStretch", ConvertValue(name, value));
		break;
	case ECostomizeParts::EyeHeight:
		owner->CostomizingInformation.EyeHeight = value;
		FaceMatInst->SetScalarParameterValue("EyeHeight", ConvertValue(name, value));
		break;
	case ECostomizeParts::EyeInterval:
		owner->CostomizingInformation.EyeInterval = value;
		FaceMatInst->SetScalarParameterValue("EyeInterval", ConvertValue(name, value));
		break;
	case ECostomizeParts::EyeSize:
		owner->CostomizingInformation.EyeSize = value;
		FaceMatInst->SetScalarParameterValue("EyeSize", ConvertValue(name, value));
		break;
	case ECostomizeParts::EyeRoation:
		owner->CostomizingInformation.EyeRoation = value;
		FaceMatInst->SetScalarParameterValue("EyeRoation", ConvertValue(name, value));
		break;
	case ECostomizeParts::EyeStretch:
		owner->CostomizingInformation.EyeStretch = value;
		FaceMatInst->SetScalarParameterValue("EyeStretch", ConvertValue(name, value));
		break;
	case ECostomizeParts::MouseHeight:
		owner->CostomizingInformation.MouseHeight = value;
		FaceMatInst->SetScalarParameterValue("MouseHeight", ConvertValue(name, value));
		break;
	case ECostomizeParts::MouseSize:
		owner->CostomizingInformation.MouseSize = value;
		FaceMatInst->SetScalarParameterValue("MouseSize", ConvertValue(name, value));
		break;
	case ECostomizeParts::MouseStretch:
		owner->CostomizingInformation.MouseStretch = value;
		FaceMatInst->SetScalarParameterValue("MouseStretch", ConvertValue(name, value));
		break;
	case ECostomizeParts::NoseHeight:
		owner->CostomizingInformation.NoseHeight = value;
		owner->CharacterPartsComponent.NoseComponent->SetRelativeLocation(FVector(.0f, .0f, ConvertValue(ECostomizeParts::NoseHeight, owner->CostomizingInformation.NoseHeight)));
		break;
	case ECostomizeParts::NoseSize:
		owner->CostomizingInformation.NoseSize = value;
		owner->CharacterPartsComponent.NoseComponent->SetRelativeScale3D(FVector(ConvertValue(ECostomizeParts::NoseStretch, owner->CostomizingInformation.NoseStretch), .0f, ConvertValue(ECostomizeParts::NoseSize, owner->CostomizingInformation.NoseSize)));
		break;
	case ECostomizeParts::NoseStretch:
		owner->CostomizingInformation.NoseStretch = value;
		owner->CharacterPartsComponent.NoseComponent->SetRelativeScale3D(FVector(ConvertValue(ECostomizeParts::NoseStretch, owner->CostomizingInformation.NoseStretch), .0f, ConvertValue(ECostomizeParts::NoseSize, owner->CostomizingInformation.NoseSize)));
		break;
	default:
		break;
	}
}

void UCostomizeManager::ModifyCostomizeTextureValue(ACostomizeCharacter* owner, ECostomizeParts name, int id)
{
	UMaterialInstanceDynamic* FaceMatInst = Cast<UMaterialInstanceDynamic>(owner->CharacterPartsComponent.HeadComponent->GetMaterial(0));
	UMaterialInstanceDynamic* BodyMatInst = Cast<UMaterialInstanceDynamic>(owner->CharacterPartsComponent.EarsComponent->GetMaterial(0));
	UMaterialInstanceDynamic* HairMatInst = Cast<UMaterialInstanceDynamic>(owner->CharacterPartsComponent.HairComponent->GetMaterial(0));
	UTexture* Tex = nullptr;
	UStaticMesh* Mesh = nullptr;
	switch (name)
	{
	case ECostomizeParts::HeadID:

		if (CostomizeItemList[(int)ECostomizeType::HEAD].Num() <= id) return;
		owner->CostomizingInformation.HeadID = id;
		Mesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(CostomizeItemList[(int)ECostomizeType::HEAD][id][1]);
		owner->CharacterPartsComponent.HeadComponent->SetStaticMesh(Mesh);
		owner->CharacterPartsComponent.HeadComponent->SetMaterialByName("Skin", FaceMatInst);
		break;
	case ECostomizeParts::HairID:
		if (CostomizeItemList[(int)ECostomizeType::HAIR].Num() <= id) return;
		owner->CostomizingInformation.HairID = id;
		Mesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(CostomizeItemList[(int)ECostomizeType::HAIR][id][1]);
		owner->CharacterPartsComponent.HairComponent->SetStaticMesh(Mesh);
		owner->CharacterPartsComponent.HairComponent->SetMaterialByName("Skin", HairMatInst);
		break;
	case ECostomizeParts::NoseID:
		if (CostomizeItemList[(int)ECostomizeType::NOSE].Num() <= id) return;
		owner->CostomizingInformation.NoseID = id;
		Mesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(CostomizeItemList[(int)ECostomizeType::NOSE][id][1]);
		owner->CharacterPartsComponent.NoseComponent->SetStaticMesh(Mesh);
		owner->CharacterPartsComponent.NoseComponent->SetMaterialByName("Skin", BodyMatInst);
		break;
	case ECostomizeParts::EarsID:
		if (CostomizeItemList[(int)ECostomizeType::EARS].Num() <= id) return;
		owner->CostomizingInformation.NoseID = id;
		Mesh = UM3GameInstance::GetResourceManager()->GetObjectFromID<UStaticMesh>(CostomizeItemList[(int)ECostomizeType::EARS][id][1]);
		owner->CharacterPartsComponent.EarsComponent->SetStaticMesh(Mesh);
		owner->CharacterPartsComponent.EarsComponent->SetMaterialByName("Skin", BodyMatInst);
		break;
	case ECostomizeParts::EyeID:
		if (CostomizeItemList[(int)ECostomizeType::EYES].Num() <= id) return;
		owner->CostomizingInformation.EyeID = id;
		Tex = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture>(CostomizeItemList[(int)ECostomizeType::EYES][id][0]);
		FaceMatInst->SetTextureParameterValue("Eyes", Tex);
		Tex = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture>(CostomizeItemList[(int)ECostomizeType::EYES][id][1]);
		FaceMatInst->SetTextureParameterValue("Pupil", Tex);
		break;
	case ECostomizeParts::EyebrowID:
		if (CostomizeItemList[(int)ECostomizeType::EYEBROW].Num() <= id) return;
		owner->CostomizingInformation.EyebrowID = id;
		Tex = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture>(CostomizeItemList[(int)ECostomizeType::EYEBROW][id][0]);
		FaceMatInst->SetTextureParameterValue("EyeBrows", Tex);
		break;
	case ECostomizeParts::MouseID:
		if (CostomizeItemList[(int)ECostomizeType::MOUSE].Num() <= id) return;
		owner->CostomizingInformation.MouseID = id;
		Tex = UM3GameInstance::GetResourceManager()->GetObjectFromID<UTexture>(CostomizeItemList[(int)ECostomizeType::MOUSE][id][0]);
		FaceMatInst->SetTextureParameterValue("Mouse", Tex);
		break;
	default:
		break;
	}
}

void UCostomizeManager::ModifyCostomizeColorValue(ACostomizeCharacter* owner, ECostomizeParts name, FColor color)
{
	UMaterialInstanceDynamic* FaceMatInst = Cast<UMaterialInstanceDynamic>(owner->CharacterPartsComponent.HeadComponent->GetMaterial(0));
	UMaterialInstanceDynamic* HairMatInst = Cast<UMaterialInstanceDynamic>(owner->CharacterPartsComponent.HairComponent->GetMaterial(0));
	UMaterialInstanceDynamic* BodyMatInst = Cast<UMaterialInstanceDynamic>(owner->CharacterPartsComponent.EarsComponent->GetMaterial(0));

	switch (name)
	{
	case ECostomizeParts::SkinColor:
		owner->CostomizingInformation.SkinColor = color;
		FaceMatInst->SetVectorParameterValue("SkinColor", color);
		BodyMatInst->SetVectorParameterValue("SkinColor", color);
		break;
	case ECostomizeParts::EyeColor:
		owner->CostomizingInformation.EyeColor = color;
		FaceMatInst->SetVectorParameterValue("EyeColor", color);
		break;
	case ECostomizeParts::MouseColor:
		owner->CostomizingInformation.MouseColor = color;
		FaceMatInst->SetVectorParameterValue("MouseColor", color);
		break;
	case ECostomizeParts::HairColor:
		owner->CostomizingInformation.HairColor = color;
		HairMatInst->SetVectorParameterValue("HairColor", color);
		break;
	case ECostomizeParts::EyeborwColor:
		owner->CostomizingInformation.EyeborwColor = color;
		FaceMatInst->SetVectorParameterValue("EyeborwColor", color);
		break;
	default:
		break;
	}
}

void UCostomizeManager::ModifyCostomizeSex(ACostomizeCharacter* owner, bool IsFemale)
{
	owner->SetupSex(IsFemale);
}

float UCostomizeManager::ConvertValue(ECostomizeParts name, float value)
{
	return MinMaxList[(int)name].Min + ((MinMaxList[(int)name].Max - MinMaxList[(int)name].Min) * FMath::Min(FMath::Max(0.0f, value), 1.0f));
}

TArray<TArray<int>>& UCostomizeManager::GetCostomizeItemList(ECostomizeType Type)
{
	return CostomizeItemList[(int)Type];
}