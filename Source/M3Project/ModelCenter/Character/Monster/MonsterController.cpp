#include "MonsterController.h"
#include "Base/M3GameInstance.h"
#include "ModelCenter/Character/PlayerCharacter/PlayerCharacter.h"
#include "ModelCenter/Character/Monster/MonsterCharacter.h"

AMonsterController::AMonsterController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MonsterFiniteStateMachine = ObjectInitializer.CreateDefaultSubobject<UMonsterFiniteStateMachine>(this, TEXT("MonsterFiniteStateMachine"));
}

void AMonsterController::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MonsterFiniteStateMachine->Tick(DeltaTime);
}