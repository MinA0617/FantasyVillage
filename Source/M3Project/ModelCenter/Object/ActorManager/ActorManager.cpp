#include "ActorManager.h"
#include <queue>
#include "Command.h"
#include "Base/M3GameInstance.h"

std::queue<CCommand*> CommandQueue;

UActorManager::UActorManager()
{
}

void UActorManager::Update(float DeltaTime)
{
	int32 Year, Month, DayOfWeek, Day, Hour, Min, Min2, Sec, Sec2, MSec, MSec2;
	FWindowsPlatformTime::SystemTime(Year, Month, DayOfWeek, Day, Hour, Min, Sec, MSec);

	const float MaxTime = DeltaTime * kTickCommandRate;
	const float StartTime = Sec + (MSec * 0.001);
	while (CommandQueue.empty() == false)
	{
		CCommand* Command = CommandQueue.front();
		if (Command)
		{
			Command->Execute();
			delete Command;
		}
		CommandQueue.pop();
		FWindowsPlatformTime::SystemTime(Year, Month, DayOfWeek, Day, Hour, Min2, Sec2, MSec2);
		if (Min != Min2) return;
		if (MaxTime < (Sec2 + (MSec2 * 0.001)) - StartTime)
		{
			return;
		}
	}
}

void UActorManager::BeginDestroy()
{
	Super::BeginDestroy();
	Clear();
}

void UActorManager::AddCommand(CCommand* Command)
{
	CommandQueue.push(Command);
}

void UActorManager::Clear()
{
	while (CommandQueue.empty() == false)
	{
		CCommand* Command = CommandQueue.front();
		if (Command)
		{
			Command->Delete();
			delete Command;
		}
		CommandQueue.pop();
	}
}

