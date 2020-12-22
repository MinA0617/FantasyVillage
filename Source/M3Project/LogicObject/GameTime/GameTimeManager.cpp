#include "GameTimeManager.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Map/MapManager.h"

void UGameTimeManager::Start()
{
	UM3GameInstance::GetInstance()->TimerManager->SetTimer(Handle, this, &UGameTimeManager::RepeatingFunction, 0.033f, true, 0.033f);
}

void UGameTimeManager::RepeatingFunction()
{
	UM3GameInstance::GetInstance()->TimerManager->ClearTimer(Handle);
	if (UM3GameInstance::IsPlaying() == false) return;
	UM3GameInstance::GetInstance()->TimerManager->SetTimer(Handle, this, &UGameTimeManager::RepeatingFunction, 0.033f, true, 0.033f);
	GameTime.Second++;
	if (GameTime.Second == 60)
	{
		GameTime.Second = 0;
		GameTime.Minute++;
		if (GameTime.Minute == 60)
		{
			GameTime.Minute = 0;
			GameTime.Hour++;
			if (GameTime.Hour == 24)
			{
				GameTime.Hour = 0;
				GameTime.Day++;
			}
		}
	}
	if(UM3GameInstance::GetMapManager()->GetWorldMap()->GetSunLight()) UM3GameInstance::GetMapManager()->GetWorldMap()->GetSunLight()->LightUpdate(GameTime);
}