#pragma once
#include "../Command.h"
#include "ModelCenter/Map/MapZone.h"
#include "Components/InstancedStaticMeshComponent.h"

class CAddInstanceCommand : public CCommand
{
public:
	struct Stock
	{
	public:
		Stock(FInstanceCubeData& target, FTransform transform, UInstancedStaticMeshComponent* mesh)
			: Target(target), Transform(transform), Mesh(mesh) {};
		FInstanceCubeData& Target;
		FTransform Transform;
		UInstancedStaticMeshComponent* Mesh;
	};
private:
	Stock* CommandStock;
public:
	void SetStock(Stock* stock)
	{
		CommandStock = stock;
	};
	void SetStock(FInstanceCubeData& target, FTransform transform, UInstancedStaticMeshComponent* mesh)
	{
		CommandStock = new Stock(target, transform, mesh);
	};
public:
	CAddInstanceCommand()
	{
		CommandStock = nullptr;
	};
	virtual ~CAddInstanceCommand()
	{
		if (CommandStock) delete CommandStock;
	};
public:
	void Execute() override
	{
		CommandStock->Mesh->AddInstance(CommandStock->Transform);
		CommandStock->Target.IsRender = true;
		delete CommandStock;
		CommandStock = nullptr;
	}
	void Delete() override
	{
		delete CommandStock;
		CommandStock = nullptr;
	}
};