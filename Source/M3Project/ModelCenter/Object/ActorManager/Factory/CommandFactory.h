#pragma once
#include "../Command/AddInstanceCommand.h"
#include "../Command/OpenZoneCommand.h"
#include "../Command/AddNPCCommand.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Object/ActorManager/ActorManager.h"

class CCommandFactory
{
public:
	CCommandFactory() {};
	~CCommandFactory() {};
	static void AddInstanceCommand(FInstanceCubeData& target, FTransform transform, UInstancedStaticMeshComponent* mesh)
	{
		CAddInstanceCommand* NewCommand = new CAddInstanceCommand;
		NewCommand->SetStock(target, transform, mesh);
		UM3GameInstance::GetActorManager()->AddCommand(NewCommand);
	};
	static void OpenZoneCommand(UMapZone* Zone, int PosX, int PosY)
	{
		COpenZoneCommand* NewCommand = new COpenZoneCommand;
		NewCommand->SetStock(Zone, PosX, PosY);
		UM3GameInstance::GetActorManager()->AddCommand(NewCommand);
	};
	static void AddNPCCommand(TArray<APawn*> List, FVector Pos, int Index)
	{
		CAddNPCCommand* NewCommand = new CAddNPCCommand;
		NewCommand->SetStock(List, Pos, Index);
		UM3GameInstance::GetActorManager()->AddCommand(NewCommand);
	};
};