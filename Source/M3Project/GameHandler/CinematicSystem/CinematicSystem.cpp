#include "CinematicSystem.h"

void UCinematicSystem::SetCinemaList(UWorld* World)
{
	CinemaList.Empty();
	for (int i = 0; i < World->LevelSequenceActors.Num(); i++)
	{
		ALevelSequenceActor* Actor = Cast<ALevelSequenceActor>(GetWorld()->LevelSequenceActors[i]);
		if (Actor)
		{
			CinemaList.Add(Actor->GetName(), Actor);
		}
	}
}

bool UCinematicSystem::PlayCinema(FString CinemaName, bool IsStopEnd)
{
	if (CinemaList.Find(CinemaName) == nullptr) return false;
	CinemaList[CinemaName]->SequencePlayer->SetPlaybackPosition(.0f);
	CinemaList[CinemaName]->SequencePlayer->Play();
	return true;
}