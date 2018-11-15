// Fill out your copyright notice in the Description page of Project Settings.

#include "DemoGameBase.h"
#include "EngineUtils.h"
#include <functional>
#include "Enemy2D.h"
#include "Player2D.h"
#include "TestPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PickupComponent.h"
#include "Item.h"


ADemoGameBase::ADemoGameBase()
{
	PrimaryActorTick.bCanEverTick = true;
	timer = (float)Spawnrate; //timer = timerValue;
	id = 0;

	PlayerControllerClass = ATestPlayerController::StaticClass();


	static ConstructorHelpers::FObjectFinder<UBlueprint> EnemyBlueprint(TEXT("Class'/Game/Blueprints/BP_Enemy2D.BP_Enemy2D'"));
	if (EnemyBlueprint.Object) 
	{
		EnemyPrefab = (UClass*)EnemyBlueprint.Object->GeneratedClass;
	}
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Class'/Game/Blueprints/BP_Item2.BP_Item2'"));
	if (ItemBlueprint.Object)
	{
		PickUpPrefab = (UClass*)ItemBlueprint.Object->GeneratedClass;
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

	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->Tags.Contains("EnemySpawn"))
		{
			EnemySpawns.Add(ActorItr->GetActorLocation());
		}
	}

#pragma endregion

	Controller = GetWorld()->GetFirstPlayerController();

	FInputModeGameOnly Inputmode;

	Controller->SetInputMode(Inputmode);
	currentLevelIndex++;

	// Find player
	UWorld* GameWorld = this->GetWorld();
	for (TActorIterator<APlayer2D> Itr(GameWorld); Itr; ++Itr)
	{
		// Filter out objects not contained in the target world.
		if (Itr->GetWorld() != GameWorld)
		{
			continue;
		}

		Player = *Itr;
	}
}

void ADemoGameBase::CheckLevel()
{
	FString CurrentLevelName = GetWorld()->GetMapName();
}


void ADemoGameBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	timer -= DeltaSeconds*5;

	///Debugger(30, timer, FString("SpawnTimer :"));

	if (EnemySpawns.Num() > 0)
	{
		if (timer <= 0)
		{
			SpawnEnemy();
			timer = timerValue;
		}
	}

	int32 enemyCount = enemies.Num();
	float playerPosX = Player->GetActorLocation().X;

	for (int32 i = 0; i < enemyCount; i++)
	{
		float enemyPosX = enemies[i]->GetActorLocation().X;
		//UE_LOG(LogTemp, Warning, TEXT("LOcATIION:  %f"), enemyLoc);
		bool bShouldwait = false;

		for (int32 j = 0; j < enemyCount; j++)
		{
			float otherEnemyPosX = enemies[j]->GetActorLocation().X;

			// if not comparing to self
			if (otherEnemyPosX != enemyPosX)
			{
				// if both are on same side of player and
				if ((enemyPosX > playerPosX && otherEnemyPosX > playerPosX) || (enemyPosX < playerPosX && otherEnemyPosX < playerPosX))
				{
					// if enemy is further to player than other enemy (we do not need to stop enemy that is in front of compared enemy)
					if (FMath::Abs((playerPosX - enemyPosX)) > FMath::Abs((playerPosX - otherEnemyPosX)))
					{
						// if valid enemies are less than 60cm apart 
						if (FMath::Abs(otherEnemyPosX - enemyPosX) < 60)
						{
							bShouldwait = true;
							//UE_LOG(LogTemp, Warning, TEXT("Waiting...."));
							//break;
						}
					}
				}
			}

			enemies[i]->bIsWaiting = bShouldwait;
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
	AEnemy2D *temp = GetWorld()->SpawnActor<AEnemy2D>(EnemyPrefab.Get(), FVector::ZeroVector, FRotator(0.0f,90.0f,0.0f), SpawnInfo);
	
	if (ProbabilityChecker())
	{
		FActorSpawnParameters wSpawnInfo;
		tempid.Empty();
		tempid.AppendInt(id);
		tempid += FString("Weapon");
		SpawnInfo.Name = FName(*tempid);
		AItem *wTemp = GetWorld()->SpawnActor<AItem>(PickUpPrefab.Get(), FVector::ZeroVector,FRotator::ZeroRotator, SpawnInfo);
		temp->AssignWeapon(wTemp);
		
	}
	temp->Tags.Add(FName("Enemy"));
	int32 spawnPoint = rand() % (EnemySpawns.Num());
	UE_LOG(LogTemp, Warning, TEXT("Spawn point chosen %d"), spawnPoint);
	temp->SetActorLocation(EnemySpawns[spawnPoint]);
	enemies.Add(temp);
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

bool ADemoGameBase::ProbabilityChecker()
{
	cumulative = 0.0f;
	diceRoll = (double)FMath::RandRange(0.0f, 100.0f);
	for (int i = 0; i < 2; i++)
	{
		cumulative += weaponEnemyChance;

		if (diceRoll < cumulative)
		{
			return true;
		}
	}

	return false;
}
