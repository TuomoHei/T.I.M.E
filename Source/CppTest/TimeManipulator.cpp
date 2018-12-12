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
	slowAudioPitch = 0.2f;
}


// Called when the game starts
void UTimeManipulator::BeginPlay()
{
	Super::BeginPlay();

	bIsSlow = true;	
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
	if (!bGameEnd)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), slowGameSpeed);

		ResetTimerHandle();

		float realSlowDuration = slowSpeedDuration * slowGameSpeed;	// E.g. 2 seconds in 0.2 x game speed should actually last one fifth of 2 seconds
		GetWorld()->GetTimerManager().SetTimer(SlowTimeHandle, this, &UTimeManipulator::DeactivateSlowmotion, realSlowDuration, false);

		UGameplayStatics::SetGlobalPitchModulation(GetWorld(), slowAudioPitch, audioPitchInterp); // set global audio pitch modulation

		if (IsValid(audioPlayer))
		{
			audioPlayer->PlaySound(5, GetWorld());
			//UE_LOG(LogTemp, Warning, TEXT("Start slow mo sound playing"));
		}

		//UE_LOG(LogTemp, Warning, TEXT("ActivateSlowmotion()"));

		bIsSlow = true;
	}
}

// Deactivate slow motion for [defaultSpeedDuration] seconds
void UTimeManipulator::DeactivateSlowmotion()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), defaultSpeed);

	ResetTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(SlowTimeHandle, this, &UTimeManipulator::ActivateSlowmotion, defaultSpeedDuration, false);
	if (IsValid(audioPlayer))
	{
		audioPlayer->PlaySound(6, GetWorld());
	}

	//UE_LOG(LogTemp, Warning, TEXT("DEactivateSlowmotion()"));

	bIsSlow = false;
}

// Deactivate slow motion until slowmo is called again manually	// Note: currently not used
void UTimeManipulator::DeactivateSlowmotionPermanent()
{
	ResetTimerHandle();
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), defaultSpeed);
	if (IsValid(audioPlayer))
	{
		audioPlayer->PlaySound(6, GetWorld());
	}

	bIsSlow = false;

	//UE_LOG(LogTemp, Warning, TEXT("DEactivateSlowmotion PERMANENT"));
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