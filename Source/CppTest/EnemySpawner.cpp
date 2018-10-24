// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
	:RightEnd(200),
	LeftEnd(-200),
	Interval(5.0f)
{
	// Entry Enemy blueprints 
	static ConstructorHelpers::FObjectFinder<UClass> FoundEnemyBP(TEXT("/Game/Blueprints/Enemy2D_BP.Enemy2D_BP_C"));
	Enemy = FoundEnemyBP.Object;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	FActorSpawnParameters Params;
	Params.bNoFail = false;

	Super::BeginPlay();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnTimer(DeltaTime);
}

void AEnemySpawner::SpawnTimer(float DeltaTime)
{
	Time += DeltaTime;
	GEngine->AddOnScreenDebugMessage(
		-1,
		GetWorld()->DeltaTimeSeconds,
		FColor::Yellow,
		"EnemySpawner:" + FString::SanitizeFloat(Time) + "/" + FString::SanitizeFloat(Interval)
	);

	if (Time >= Interval)
	{
		Spawn();
		Time = 0.0f;
	}
}

void AEnemySpawner::Spawn()
{
	FVector SpawnPoint;
	//SpawnPoint.X = rand() % int(RightEnd - LeftEnd) + LeftEnd;
	//SpawnPoint.Y = 0;
	//SpawnPoint.Z = 50;

	SpawnPoint = this->GetActorLocation();

	UWorld* World = GetWorld();
	World->SpawnActor<AEnemy2D>(Enemy, SpawnPoint, FRotator::ZeroRotator);
}

