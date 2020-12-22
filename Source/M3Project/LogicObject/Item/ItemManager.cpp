#include "ItemManager.h"
#include "ConstructorHelpers.h"
#include "Base/M3GameInstance.h"
#include "Resource/M3ResourceManager.h"

UItemManager::UItemManager()
{
	FString WeaponDataPath = TEXT("DataTable'/Game/Resource/ResourceTable/WeaponItemTable.WeaponItemTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_Weapon(*WeaponDataPath);
	if (DT_Weapon.Succeeded()) WeaponItemTable = DT_Weapon.Object;

	FString EquipmentDataPath = TEXT("DataTable'/Game/Resource/ResourceTable/EquipmentItemTable.EquipmentItemTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_Equipment(*EquipmentDataPath);
	if (DT_Equipment.Succeeded()) EquipmentItemTable = DT_Equipment.Object;

	FString ConsumptionDataPath = TEXT("DataTable'/Game/Resource/ResourceTable/ConsumptionItemTable.ConsumptionItemTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_Consumption(*ConsumptionDataPath);
	if (DT_Consumption.Succeeded()) ConsumptionItemTable = DT_Consumption.Object;

	FString ResourceDataPath = TEXT("DataTable'/Game/Resource/ResourceTable/ResourceItemTable.ResourceItemTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_Resource(*ResourceDataPath);
	if (DT_Resource.Succeeded()) ResourceItemTable = DT_Resource.Object;

	FString InstallationDataPath = TEXT("DataTable'/Game/Resource/ResourceTable/InstallationItemTable.InstallationItemTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DT_Installation(*InstallationDataPath);
	if (DT_Installation.Succeeded()) InstallationItemTable = DT_Installation.Object;
}

UItemBase* UItemManager::GetItem(EItemType Type, int ID)
{
	switch (Type)
	{
	case EItemType::RESOURCE:
		return GetResourceItem(ID);
		break;
	case EItemType::CONSUMPTION:
		return GetConsumptionItem(ID);
		break;
	case EItemType::EQUIPMENT:
		return GetEquipmentItem(ID);
		break;
	case EItemType::WEAPON:
		return GetWeaponItem(ID);
		break;
	case EItemType::INSTALLATION:
		return GetInstallationItem(ID);
		break;
	}
	return nullptr;
}

UWeaponItem* UItemManager::GetWeaponItem(int ID)
{
	FWeaponItemTableResource* Data = WeaponItemTable->FindRow<FWeaponItemTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
	if (Data == nullptr) return nullptr;
	UWeaponItem* Weapon = NewObject<UWeaponItem>();
	Weapon->DefaultInfo.ID				= ID;
	Weapon->DefaultInfo.Name			= Data->Name;
	Weapon->DefaultInfo.IconResource	= Data->IconResource;
	Weapon->DefaultInfo.MeshResource	= Data->MeshResource;
	Weapon->DefaultInfo.Type			= Data->Type;
	Weapon->DefaultInfo.SubType			= Data->SubType;
	Weapon->DefaultInfo.WeaponLenght	= Data->WeaponLenght;
	Weapon->DefaultInfo.AttackPoint		= Data->AttackPoint;
	Weapon->DefaultInfo.ToolTip			= Data->ToolTip;
	AsyncItemResourceLoad(EItemType::WEAPON, ID);
	return Weapon;
}

UEquipmentItem* UItemManager::GetEquipmentItem(int ID)
{
	FEquipmentItemTableResource* Data = EquipmentItemTable->FindRow<FEquipmentItemTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
	if (Data == nullptr) return nullptr;
	UEquipmentItem* Equipment = NewObject<UEquipmentItem>();
	Equipment->DefaultInfo.ID = ID;
	Equipment->DefaultInfo.Name = Data->Name;
	Equipment->DefaultInfo.IconResource = Data->IconResource;
	Equipment->DefaultInfo.MeshResource = Data->MeshResource;
	Equipment->DefaultInfo.Type = Data->Type;
	Equipment->DefaultInfo.SubType = Data->SubType;
	Equipment->DefaultInfo.ToolTip = Data->ToolTip;
	AsyncItemResourceLoad(EItemType::EQUIPMENT, ID);
	return Equipment;
}

UConsumptionItem* UItemManager::GetConsumptionItem(int ID)
{
	FConsumptionItemTableResource* Data = ConsumptionItemTable->FindRow<FConsumptionItemTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
	if (Data == nullptr) return nullptr;
	UConsumptionItem* Consumption = NewObject<UConsumptionItem>();
	Consumption->DefaultInfo.ID = ID;
	Consumption->DefaultInfo.Name = Data->Name;
	Consumption->DefaultInfo.IconResource = Data->IconResource;
	Consumption->DefaultInfo.RecoveryHP = Data->RecoveryHP;
	Consumption->DefaultInfo.ToolTip = Data->ToolTip;
	AsyncItemResourceLoad(EItemType::CONSUMPTION, ID);
	return Consumption;
}

UResourceItem* UItemManager::GetResourceItem(int ID)
{
	FResourceItemTableResource* Data = ResourceItemTable->FindRow<FResourceItemTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
	if (Data == nullptr) return nullptr;
	UResourceItem* Resource = NewObject<UResourceItem>();
	Resource->DefaultInfo.ID = ID;
	Resource->DefaultInfo.Name = Data->Name;
	Resource->DefaultInfo.IconResource = Data->IconResource;
	Resource->DefaultInfo.MeshResource = Data->MeshResource;
	Resource->DefaultInfo.ToolTip = Data->ToolTip;
	AsyncItemResourceLoad(EItemType::RESOURCE, ID);
	return Resource;
}

UInstallationItem* UItemManager::GetInstallationItem(int ID)
{
	FInstallationItemTableResource* Data = InstallationItemTable->FindRow<FInstallationItemTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
	if (Data == nullptr) return nullptr;
	UInstallationItem* Installation = NewObject<UInstallationItem>();
	Installation->DefaultInfo.ID = ID;
	Installation->DefaultInfo.Name = Data->Name;
	Installation->DefaultInfo.IconResource = Data->IconResource;
	Installation->DefaultInfo.MeshResource = Data->MeshResource;
	Installation->DefaultInfo.Type = Data->Type;
	Installation->DefaultInfo.SubType = (EInstallationType)Data->SubType;
	Installation->DefaultInfo.ToolTip = Data->ToolTip;
	AsyncItemResourceLoad(EItemType::INSTALLATION, ID);
	return Installation;
}

void UItemManager::AsyncItemResourceLoad(EItemType Type, int ID)
{
	TArray<int> LoadList;
	switch (Type)
	{
	case EItemType::RESOURCE:
	{
		FResourceItemTableResource* Data = ResourceItemTable->FindRow<FResourceItemTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
		if (Data == nullptr) return;
		LoadList.Add(Data->MeshResource);
		LoadList.Add(Data->IconResource);
	}
	break;
	case EItemType::CONSUMPTION:
	{
		FConsumptionItemTableResource* Data = ConsumptionItemTable->FindRow<FConsumptionItemTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
		if (Data == nullptr) return;
		LoadList.Add(Data->IconResource);
	}
	break;
	case EItemType::EQUIPMENT:
	{
		FEquipmentItemTableResource* Data = EquipmentItemTable->FindRow<FEquipmentItemTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
		if (Data == nullptr) return;
		LoadList.Add(Data->MeshResource);
		LoadList.Add(Data->IconResource);
	}
	break;
	case EItemType::WEAPON:
	{
		FWeaponItemTableResource* Data = WeaponItemTable->FindRow<FWeaponItemTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
		if (Data == nullptr) return;
		LoadList.Add(Data->MeshResource);
		LoadList.Add(Data->IconResource);
	}
	break;
	case EItemType::INSTALLATION:
	{
		FInstallationItemTableResource* Data = InstallationItemTable->FindRow<FInstallationItemTableResource>(FName(*(FString::FromInt(ID))), TEXT("z"));
		if (Data == nullptr) return;
		LoadList.Add(Data->MeshResource);
		LoadList.Add(Data->IconResource);
	}
	break;
	}
	for (int i = 0; i < LoadList.Num(); i++)
	{
		UM3GameInstance::GetResourceManager()->OrderAsyncLoad(LoadList[i]);
	}
}