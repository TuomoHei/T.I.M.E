// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneScoreActor.h"
//#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ASceneScoreActor::ASceneScoreActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("ScoreActor");

	MultiplierTimer = 0.0f;
	ScoreMultiplier = 1;
	bIsPaused = false;
}

// Called when the game starts or when spawned
void ASceneScoreActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneScoreActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float gameSpeed = UGameplayStatics::GetGlobalTimeDilation(GetWorld());

	if (gameSpeed == 0.0f) { gameSpeed = 1.0f; }

	if (!bIsPaused && MultiplierTimer > 0.0f)
	{
		MultiplierTimer -= DeltaTime / gameSpeed;

		if (MultiplierTimer < 0.0f)
		{
			if (ScoreMultiplier > 2)
			{
				MultiplierTimer = MultiplierTimerAddition;
			}
			else
			{
				MultiplierTimer = 0.0f;
			}
			ScoreMultiplier--;
		}
	}

	//GEngine->AddOnScreenDebugMessage(1334, 5.0f, FColor::Green, FString::Printf(TEXT("Score multiplier: %i"), ScoreMultiplier));
	//GEngine->AddOnScreenDebugMessage(1335, 5.0f, FColor::Green, FString::Printf(TEXT("Current time: %f"), MultiplierTimer));
}

void ASceneScoreActor::AddPoints(int points)
{
	CurrentScore += FMath::Abs(points * ScoreMultiplier++);
	MultiplierTimer = MultiplierTimerAddition;
	//GEngine->AddOnScreenDebugMessage(70, 5.0f, FColor::Green, FString::Printf(TEXT("Current score: %i"), CurrentScore));
}

void ASceneScoreActor::ResetCurrentScore()
{
	CurrentScore = 0;
	MultiplierTimer = 0.0f;
	ScoreMultiplier = 1;
}
