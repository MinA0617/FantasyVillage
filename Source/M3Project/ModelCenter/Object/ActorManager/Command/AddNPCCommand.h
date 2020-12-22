#pragma once
#include "../Command.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/CharacterManager.h"

class CAddNPCCommand : public CCommand
{
public:
	struct Stock
	{
	public:
		Stock(TArray<APawn*> list, FVector pos, int index)
			: List(list), Pos(pos), Index(index) {};
		TArray<APawn*> List;
		FVector Pos;
		int Index;
	};
private:
	Stock* CommandStock;
public:
	void SetStock(Stock* stock)
	{
		CommandStock = stock;
	};
	void SetStock(TArray<APawn*> List, FVector pos, int index)
	{
		CommandStock = new Stock(List, pos, index);
	};
public:
	CAddNPCCommand()
	{
		CommandStock = nullptr;
	};
	virtual ~CAddNPCCommand()
	{
		if (CommandStock) delete CommandStock;
	};
public:
	void Execute() override
	{
		if (UM3GameInstance::GetCharacterManager()->IsMonster(CommandStock->Index))
		{
			APawn* Pawn = UM3GameInstance::GetCharacterManager()->SpawnMonster(CommandStock->Pos, CommandStock->Index);
			CommandStock->List.Add(Pawn);
		}
		else
		{
			//SpawnNPC
		}
		delete CommandStock;
		CommandStock = nullptr;
	}
	void Delete() override
	{
		delete CommandStock;
		CommandStock = nullptr;
	}
};