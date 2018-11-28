// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeManipulator.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "../../Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values for this component's properties
UTimeManipulator::UTimeManipulator()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UTimeManipulator::BeginPlay()
{
	Super::BeginPlay();

	bIsSlow = true;
	ActivateSlowmotion();
}


// Called every frame
void UTimeManipulator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Debug timer for slow motion
	float timeToDilation = GetWorld()->GetTimerManager().GetTimerRemaining(SlowTimeHandle);	// -1 = infinite
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Time to next speed change = %f"), timeToDilation));
}

// Activate slow motion for [slowSpeedDuration] seconds
void UTimeManipulator::ActivateSlowmotion()
{	
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), slowGameSpeed);	

	ResetTimerHandle();

	float realSlowDuration = slowSpeedDuration * slowGameSpeed;	// E.g. 2 seconds in 0.2 x game speed should actually last one fifth of 2 seconds
	GetWorld()->GetTimerManager().SetTimer(SlowTimeHandle, this, &UTimeManipulator::DeactivateSlowmotion, realSlowDuration, false);		
	UGameplayStatics::SetGlobalPitchModulation(GetWorld(), 0.01f, realSlowDuration);
	//UGameplayStatics::PlaySoundAtLocation(GetWorld(), sound, GetOwner()->GetActorLocation());
	
	UE_LOG(LogTemp, Warning, TEXT("ActivateSlowmotion()"));

	bIsSlow = true;
}

// Deactivate slow motion for [defaultSpeedDuration] seconds
void UTimeManipulator::DeactivateSlowmotion()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), defaultSpeed);

	ResetTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(SlowTimeHandle, this, &UTimeManipulator::ActivateSlowmotion, defaultSpeedDuration, false);
	
	bIsSlow = false;
}

// Deactivate slow motion until slowmo is called again manually	// Note: currently not used
void UTimeManipulator::DeactivateSlowmotionPermanent()
{
	ResetTimerHandle();
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), defaultSpeed);
}

void UTimeManipulator::ResetTimerHandle()
{
	GetWorld()->GetTimerManager().ClearTimer(SlowTimeHandle);
}



/*// USAGE EXAMPLE
player.h

void GetTimeManipulator();

UPROPERTY(EditAnywhere)
	UTimeManipulator* timeManager;

player.cpp

// begin play
GetTimeManipulator();

// at bottom
void APlayer2D::GetTimeManipulator()
{
	timeManager = FindComponentByClass<UTimeManipulator>();
	if (timeManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time Manipulator found"));
	}
}

*/