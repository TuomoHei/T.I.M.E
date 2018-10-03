// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeManipulator.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "../../Engine/Public/TimerManager.h"



// Sets default values for this component's properties
UTimeManipulator::UTimeManipulator()

{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTimeManipulator::BeginPlay()
{
	Super::BeginPlay();
	Position = GetOwner()->GetActorLocation();
	OldPosition = Position;
	pTimeManager = ATimeManager::GetInstance(this);
	// ...
	
}


// Called every frame
void UTimeManipulator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Compare psosion to before frame to detect speed
	OldPosition = Position;
	Position = GetOwner()->GetActorLocation();

	// Compare Speed to before frame to change slow mode
	OldSpeed = Speed;
	Speed = (Position - OldPosition).Size();


	// Detect change Speed
	if (Speed == 0.0f && OldSpeed != 0.0f)
	{
		ChangeSlow();
	}
	else if (Speed != 0.0f && OldSpeed == 0.0f)
	{
		ChangeNormal();
	}
}

void UTimeManipulator::ChangeSlow()
{
	pTimeManager->StartSlow();
}

void UTimeManipulator::ChangeNormal()
{
	pTimeManager->StopSlow();
}

void UTimeManipulator::Action(float regainTime)
{
	ChangeNormal();
}
