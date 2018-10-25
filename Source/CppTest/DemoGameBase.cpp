// Fill out your copyright notice in the Description page of Project Settings.

#include "DemoGameBase.h"
#include <functional>
#include "Enemy2D.h"
#include "Player2D.h"
#include "TestPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include <list>
#include "Player2D.h"


ADemoGameBase::ADemoGameBase()
{
	PrimaryActorTick.bCanEverTick = true;
	timer = timerValue;
	id = 0;

	PlayerControllerClass = ATestPlayerController::StaticClass();


	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_Enemy2D.BP_Enemy2D'"));
	if (ItemBlueprint.Object) 
	{
		Debugger(2400, 0, FString("Found object"));
		EnemyPrefab = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}
}

void ADemoGameBase::StartPlay()
{
	Super::StartPlay();

	//Contains iterators that populate lists declared in header
#pragma region Listpopulators

	TArray<AActor*> FoundPlayers;
	currentLevelIndex = 0;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayer2D::StaticClass(), FoundPlayers);
	if (FoundPlayers.Num() >= 2 || FoundPlayers.Num() <= 0)
	{
		Debugger(5, 0, FString("Error on startingplay / Player "));
		return;
	}
	else
	{
		Debugger(2, 0, FoundPlayers[0]->GetActorLabel());
	}


	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->Tags.Contains("EnemySpawn"))
		{
			EnemySpawns.Add(ActorItr->GetActorLocation());
		}
	}

	Debugger(125, EnemySpawns.Num(), FString("AAA"));

#pragma endregion

	//Debug region here (remove when no longer needed)
#pragma region DEBUG

	//Debugger(3, FoundPlayers.Num(), FString("PlayerCount : "));
	//Debugger(4, EnemySpawns.Num(), FString("Enemyspawn count : "));


#pragma endregion

	Controller = GetWorld()->GetFirstPlayerController();

	FInputModeGameOnly Inputmode;

	Controller->SetInputMode(Inputmode);
	currentLevelIndex++;
}

void ADemoGameBase::CheckLevel()
{
	FString CurrentLevelName = GetWorld()->GetMapName();
}


void ADemoGameBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	timer -= DeltaSeconds;

	///Debugger(30, timer, FString("SpawnTimer :"));

	if (EnemySpawns.Num() > 0)
	{
		if (timer <= 0)
		{
			SpawnEnemy();
			timer = timerValue;
		}
	}
}

void ADemoGameBase::SpawnEnemy()
{
	if (id >= 1000) id = 0;

	if (!EnemyPrefab)
	{
		Debugger(1000, 0, FString("Disabled enemy spawning"));
		return;
	}
	FActorSpawnParameters SpawnInfo;
	FString tempid;
	tempid.AppendInt(id);
	tempid += FString("Enemy");
	SpawnInfo.Name = FName(*tempid);
	AEnemy2D *temp = GetWorld()->SpawnActor<AEnemy2D>(EnemyPrefab.Get(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
	temp->SetActorLocation(EnemySpawns[0]);
	Debugger(1, 0, FString("Spawning "));
	id++;
}

void ADemoGameBase::EndLevel()
{
	FString LevelString = GetWorld()->GetMapName();
	FName LevelToLoad = FName(*LevelString);
}

//debugger which includes GEngine : Level is priority of message, disp is a value that you need to be displayed
void ADemoGameBase::Debugger(int level = 0, int disp = 0, FString message = " ")
{
	FString temp;
	temp.AppendInt(disp);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(level, 5.f, FColor::Yellow, message + "  " + temp);
	}
}

void ADemoGameBase::OnPlayerDeath()
{
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy2D::StaticClass(), temp);
	
	int i = 0;
	for (int i = 0; i < temp.Num(); i++)
	{
		AEnemy2D *enemy = Cast<AEnemy2D>(temp[i]);
		enemy->PlayerDeath();
	}
}
