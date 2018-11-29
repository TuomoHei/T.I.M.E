// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioPlayer.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
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
	if (sounds[soundIndex] == nullptr)
	{
		sound = sounds[soundIndex];

		UGameplayStatics::PlaySoundAtLocation(w, sound, defaultLocation);
	}
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


// Called every frame
//void AAudioPlayer::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

