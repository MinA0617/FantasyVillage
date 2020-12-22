// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterFiniteStateMachine/MonsterFiniteStateMachine.h"
#include "MonsterController.generated.h"

UCLASS()
class M3PROJECT_API AMonsterController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterController(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY()
    UMonsterFiniteStateMachine* MonsterFiniteStateMachine;
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
public:
	FVector HomeLocation;
};
