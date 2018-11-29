// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioPlayer.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


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

	world = GetWorld();
}

void AAudioPlayer::PlaySound(int soundIndex)
{
	sound = sounds[soundIndex];
	
	UGameplayStatics::PlaySoundAtLocation(world, sound, GetOwner()->GetActorLocation());
}

void AAudioPlayer::PlaySound(int soundIndex, FVector location)
{
	sound = sounds[soundIndex];

	UGameplayStatics::PlaySoundAtLocation(world, sound, location);
}


// Called every frame
//void AAudioPlayer::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

