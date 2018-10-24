// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeManager.h"
#include "Engine/World.h"
#include "Engine/Classes/Engine/Engine.h"
#include "SlowComponent.h"
#include "EngineUtils.h"
#include "Engine/Classes/GameFramework/Actor.h"

ATimeManager* ATimeManager::Instance = nullptr;

// Sets default values
ATimeManager::ATimeManager()
	:TimeLimit(5.0f),
	SlowRate(0.2f),
	DefaultRate(1.0f)
{
	Instance = nullptr;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	USlowComponent::SetSpeed(SlowRate);

	CurrentTime = TimeLimit;
	bIsSlow = true;
	bForcedSlow = false;
}

// Called every frame
void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(
		-1, 
		GetWorld()->DeltaTimeSeconds,
		FColor::Yellow, 
		"CurrentTime:" + FString::SanitizeFloat(CurrentTime) + "/" + FString::SanitizeFloat(TimeLimit)
	);

	if (bIsSlow)
	{
		CurrentTime -= GetWorld()->DeltaTimeSeconds;
	}

	if (CurrentTime <= 0.0f)
	{
		CurrentTime = 0.0f;
		StopSlow();
	}
}

void ATimeManager::FindInstance(UObject* WorldContextObject)
{
	UWorld* world = WorldContextObject->GetWorld();

	for (TActorIterator<ATimeManager> ActItr(world); ActItr; ++ActItr)
	{
		Instance = *ActItr;
		return;
	}
}

ATimeManager* ATimeManager::GetInstance(UObject* WorldContextObject)
{
	if (Instance)
	{
		return Instance;
	}

	// Find Actor TimeManager Actor
	FindInstance(WorldContextObject);
	return Instance;
}

void ATimeManager::StartSlow()
{
	if (CurrentTime <= 0.0f)
		return;
	bIsSlow = true;

	USlowComponent::SetSpeed(SlowRate);
}

void ATimeManager::StopSlow()
{
	bIsSlow = false;
	bForcedSlow = false;
	CurrentTime = TimeLimit;
	USlowComponent::SetSpeed(DefaultRate);

}
