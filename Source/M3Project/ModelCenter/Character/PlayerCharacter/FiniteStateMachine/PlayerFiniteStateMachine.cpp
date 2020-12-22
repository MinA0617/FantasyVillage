#include "PlayerFiniteStateMachine.h"
#include "FiniteState/PlayerFiniteState_Attack.h"
#include "FiniteState/PlayerFiniteState_Battle.h"
#include "FiniteState/PlayerFiniteState_Build.h"
#include "FiniteState/PlayerFiniteState_Defualt.h"
#include "FiniteState/PlayerFiniteState_DefualtReact.h"
#include "FiniteState/PlayerFiniteState_React.h"
#include "FiniteState/PlayerFiniteState_Dead.h"
#include "FiniteState/PlayerFiniteState_Dialogue.h"
#include "FiniteState/PlayerFiniteState_BuildReact.h"

UPlayerFiniteStateMachine::UPlayerFiniteStateMachine(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerFiniteStateList.SetNum((int)EPlayerState::__MAX__);

	PlayerFiniteStateList[(int)EPlayerState::DEFUALT] = ObjectInitializer.CreateDefaultSubobject<UPlayerFiniteState_Defualt>(this, TEXT("FSM_Defualt"));
	PlayerFiniteStateList[(int)EPlayerState::BATTLE] = ObjectInitializer.CreateDefaultSubobject<UPlayerFiniteState_Battle>(this, TEXT("FSM_Battle"));
	PlayerFiniteStateList[(int)EPlayerState::ATTACK] = ObjectInitializer.CreateDefaultSubobject<UPlayerFiniteState_Attack>(this, TEXT("FSM_Attack"));
	PlayerFiniteStateList[(int)EPlayerState::BUILD] = ObjectInitializer.CreateDefaultSubobject<UPlayerFiniteState_Build>(this, TEXT("FSM_Build"));
	PlayerFiniteStateList[(int)EPlayerState::DEFUALT_REACT] = ObjectInitializer.CreateDefaultSubobject<UPlayerFiniteState_DefualtReact>(this, TEXT("FSM_DefualtReact"));
	PlayerFiniteStateList[(int)EPlayerState::REACT] = ObjectInitializer.CreateDefaultSubobject<UPlayerFiniteState_React>(this, TEXT("FSM_React"));
	PlayerFiniteStateList[(int)EPlayerState::BUILD_REACT] = ObjectInitializer.CreateDefaultSubobject<UPlayerFiniteState_BuildReact>(this, TEXT("FSM_BuildReact"));
	PlayerFiniteStateList[(int)EPlayerState::DIALOGUE] = ObjectInitializer.CreateDefaultSubobject<UPlayerFiniteState_Dialogue>(this, TEXT("FSM_Dialogue"));
	PlayerFiniteStateList[(int)EPlayerState::DEAD] = ObjectInitializer.CreateDefaultSubobject<UPlayerFiniteState_Dead>(this, TEXT("FSM_Dead"));

	CurrentPlayerState = PlayerFiniteStateList[(int)EPlayerState::DEFUALT];

	AddFiniteState(EPlayerState::DEFUALT,		EPlayerEvent::BATTLE_START,			EPlayerState::BATTLE);
	AddFiniteState(EPlayerState::BATTLE,		EPlayerEvent::RETURN_DEFUALT,		EPlayerState::DEFUALT);
	AddFiniteState(EPlayerState::BATTLE,		EPlayerEvent::ATTACK_START,			EPlayerState::ATTACK);
	AddFiniteState(EPlayerState::ATTACK,		EPlayerEvent::BATTLE_START,			EPlayerState::BATTLE);
	AddFiniteState(EPlayerState::BUILD,			EPlayerEvent::RETURN_DEFUALT,		EPlayerState::DEFUALT);
	AddFiniteState(EPlayerState::BUILD,			EPlayerEvent::BATTLE_START,			EPlayerState::BATTLE);
	AddFiniteState(EPlayerState::DEFUALT,		EPlayerEvent::BUILD_START,			EPlayerState::BUILD);

	AddFiniteState(EPlayerState::DEFUALT,		EPlayerEvent::REACT_START,			EPlayerState::DEFUALT_REACT);
	AddFiniteState(EPlayerState::BATTLE,		EPlayerEvent::REACT_START,			EPlayerState::REACT);
	AddFiniteState(EPlayerState::ATTACK,		EPlayerEvent::REACT_START,			EPlayerState::REACT);
	AddFiniteState(EPlayerState::BUILD,			EPlayerEvent::REACT_START,			EPlayerState::BUILD_REACT);
	AddFiniteState(EPlayerState::DIALOGUE,		EPlayerEvent::REACT_START,			EPlayerState::DEFUALT_REACT);

	AddFiniteState(EPlayerState::DEFUALT,		EPlayerEvent::DEAD_START,			EPlayerState::DEAD);
	AddFiniteState(EPlayerState::BATTLE,		EPlayerEvent::DEAD_START,			EPlayerState::DEAD);
	AddFiniteState(EPlayerState::ATTACK,		EPlayerEvent::DEAD_START,			EPlayerState::DEAD);
	AddFiniteState(EPlayerState::BUILD,			EPlayerEvent::DEAD_START,			EPlayerState::DEAD);
	AddFiniteState(EPlayerState::REACT,			EPlayerEvent::DEAD_START,			EPlayerState::DEAD);
	AddFiniteState(EPlayerState::DEFUALT_REACT,	EPlayerEvent::DEAD_START,			EPlayerState::DEAD);
	AddFiniteState(EPlayerState::BUILD_REACT,	EPlayerEvent::DEAD_START,			EPlayerState::DEAD);
	AddFiniteState(EPlayerState::DIALOGUE,		EPlayerEvent::DEAD_START,			EPlayerState::DEAD);

	AddFiniteState(EPlayerState::REACT,			EPlayerEvent::REACT_START,			EPlayerState::REACT);
	AddFiniteState(EPlayerState::REACT,			EPlayerEvent::BATTLE_START,			EPlayerState::BATTLE);
	AddFiniteState(EPlayerState::DEFUALT_REACT, EPlayerEvent::REACT_START,			EPlayerState::DEFUALT_REACT);
	AddFiniteState(EPlayerState::DEFUALT_REACT, EPlayerEvent::RETURN_DEFUALT,		EPlayerState::DEFUALT);
	AddFiniteState(EPlayerState::BUILD_REACT,	EPlayerEvent::REACT_START,			EPlayerState::BUILD_REACT);
	AddFiniteState(EPlayerState::BUILD_REACT,	EPlayerEvent::BUILD_START,			EPlayerState::BUILD);

	AddFiniteState(EPlayerState::DEFUALT,		EPlayerEvent::DIALOGUE_START,		EPlayerState::DIALOGUE);
	AddFiniteState(EPlayerState::DIALOGUE,		EPlayerEvent::RETURN_DEFUALT,		EPlayerState::DEFUALT);

	AddFiniteState(EPlayerState::DEAD,			EPlayerEvent::RETURN_DEFUALT,		EPlayerState::DEFUALT);
}


void UPlayerFiniteStateMachine::AddFiniteState(EPlayerState state, EPlayerEvent stateevent, EPlayerState nextstate)
{
	if (StateMachineList.Find(state) == nullptr)
	{
		StateMachineList.Add(state, TMap<EPlayerEvent, EPlayerState>());
	}
	StateMachineList[state].Add(stateevent, nextstate);
}

void UPlayerFiniteStateMachine::StateEvent(EPlayerEvent Event)
{
	EPlayerState NextState = StateMachineList[CurrentPlayerState->State][Event];
	CurrentPlayerState->Release();
	CurrentPlayerState = PlayerFiniteStateList[(int)NextState];
	CurrentPlayerState->Init(Owner);
}

void UPlayerFiniteStateMachine::Init(APlayerCharacter* owner)
{
	Owner = owner;
	CurrentPlayerState->Init(Owner);
}

void UPlayerFiniteStateMachine::MouseLeftClick()
{
	CurrentPlayerState->MouseLeftClick();
}

void UPlayerFiniteStateMachine::MouseRightClick()
{
	CurrentPlayerState->MouseRightClick();
}

void UPlayerFiniteStateMachine::MouseLeftRelease()
{
	CurrentPlayerState->MouseLeftRelease();
}

void UPlayerFiniteStateMachine::MouseRightRelease()
{
	CurrentPlayerState->MouseRightRelease();
}

void UPlayerFiniteStateMachine::MouseWheel(float Value)
{
	CurrentPlayerState->MouseWheel(Value);
}

void UPlayerFiniteStateMachine::JumpAction()
{
	CurrentPlayerState->JumpAction();
}

void UPlayerFiniteStateMachine::MoveForward(float Value)
{
	CurrentPlayerState->MoveForward(Value);
}

void UPlayerFiniteStateMachine::MoveRight(float Value)
{
	CurrentPlayerState->MoveRight(Value);
}

void UPlayerFiniteStateMachine::BattleOn()
{
	CurrentPlayerState->BattleOn();
}

void UPlayerFiniteStateMachine::BuildOn()
{
	CurrentPlayerState->BuildOn();
}

void UPlayerFiniteStateMachine::Enter()
{
	CurrentPlayerState->Enter();
}

void UPlayerFiniteStateMachine::Tick(float DeltaSecond)
{
	CurrentPlayerState->Tick(DeltaSecond);
}