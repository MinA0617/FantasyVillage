#pragma once
#include "../Command.h"
#include "ModelCenter/Map/MapZone.h"
#include "Base/M3GameInstance.h"
#include "Resource/SaveData/SaveManager.h"
#include "Components/InstancedStaticMeshComponent.h"

class COpenZoneCommand : public CCommand
{
public:
	struct Stock
	{
	public:
		Stock(UMapZone* zone, int posx, int posy)
			: Zone(zone), PosX(posx), PosY(posy) {};
		UMapZone* Zone;
		int PosX;
		int PosY;
	};
private:
	Stock* CommandStock;
public:
	void SetStock(Stock* stock)
	{
		CommandStock = stock;
	};
	void SetStock(UMapZone* zone, int posx, int posy)
	{
		CommandStock = new Stock(zone, posx, posy);
	};
public:
	COpenZoneCommand()
	{
		CommandStock = nullptr;
	};
	virtual ~COpenZoneCommand()
	{
		if (CommandStock) delete CommandStock;
	};
public:
	void Execute() override
	{
		FZoneData ZoneData;
		UM3GameInstance::GetSaveManager()->LoadZoneData(UM3GameInstance::GetSaveManager()->GetIndex(), ZoneData, CommandStock->PosX, CommandStock->PosY);
		CommandStock->Zone->Load(ZoneData);
		CommandStock->Zone->Open(false);
		delete CommandStock;
		CommandStock = nullptr;
	}
	void Delete() override
	{
		delete CommandStock;
		CommandStock = nullptr;
	}
};