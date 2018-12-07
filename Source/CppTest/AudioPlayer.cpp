// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioPlayer.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
//#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values
AAudioPlayer::AAudioPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAudioPlayer::BeginPlay()
{
	Super::BeginPlay();

	//defaultLocation = GetWorld()->GetFirstPlayerController()->GetTransform().GetLocation();
	defaultLocation = FVector::ZeroVector;
}

void AAudioPlayer::PlaySound(int soundIndex, UWorld * w)
{
	// Play sound by index
//	sound = sounds[soundIndex];

//	UGameplayStatics::PlaySoundAtLocation(w, sound, defaultLocation);

	//UE_LOG(LogTemp, Warning, TEXT("Playing audio"));
}

void AAudioPlayer::PlaySound(int soundIndex, float delay, UWorld * w) // problem: can't have two delays with same timer.. hmmm.... or can we?
{
	// Play sound by index after delay

	ResetTimerHandle(w);
	//FTimerHandle DelayTimeHandle;
	FTimerDelegate AudioDelayDelegate = FTimerDelegate::CreateUObject(this, &AAudioPlayer::PlaySound, soundIndex, w);
	GetWorldTimerManager().SetTimer(DelayTimeHandle, AudioDelayDelegate, delay, false);
	//w->GetTimerManager().SetTimer(DelayTimeHandle, this, &AAudioPlayer::PlaySound, defaultSpeedDuration, false);	

}

// Play sound at location by index
void AAudioPlayer::PlaySound(int soundIndex, FVector location, UWorld * w)
{
	if (sounds[soundIndex] == nullptr)
	{
		sound = sounds[soundIndex];
	
		UGameplayStatics::PlaySoundAtLocation(w, sound, location);
	}
}

void AAudioPlayer::ResetTimerHandle(UWorld * world)
{
	world->GetTimerManager().ClearTimer(DelayTimeHandle);
}


// Called every frame
//void AAudioPlayer::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

