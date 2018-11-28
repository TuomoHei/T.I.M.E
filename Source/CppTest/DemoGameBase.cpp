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
	enemyCount = 0;
	PlayerControllerClass = ATestPlayerController::StaticClass();
}

ADemoGameBase::~ADemoGameBase()
{
	indexWep = 0;
}


void ADemoGameBase::StartPlay()
{

	auto PC = Cast<ATestPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC) PC->RegisterGameBase(this);
	Super::StartPlay();
	enemyCount = 0;
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

	FVector SpawnPosition = FVector(0.f, 0.f, 0.f);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Name = FName(*Entityname(FString("AudioPlayer"), 0));
	//audioPlayer = GetWorld()->SpawnActor<AAudioPlayer>(AAudioPlayer::StaticClass(), SpawnPosition, FRotator::ZeroRotator, SpawnInfo);
	audioPlayer = GetWorld()->SpawnActor<AAudioPlayer>(SpawnPosition, FRotator::ZeroRotator, SpawnInfo);
}


void ADemoGameBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	timer -= DeltaSeconds * 5;

	if (EnemySpawns.Num() > 0)
	{
		if (timer <= 0)
		{
			SpawnEnemy();
			timer = timerValue;
		}
	}

	enemyCount = enemies.Num();
	float playerPosX = Player->GetActorLocation().X;
	int firstEnemyLeft = -1;
	int firstEnemyRight = -1;	

	// Make enemy wait behind enemy in front of him if condition are met
	for (int32 i = 0; i < enemyCount; i++)
	{
		if (IsValid(enemies[i]))
		{
			float enemyPosX = enemies[i]->GetActorLocation().X;
			float enemyDistToPlayer = FMath::Abs(playerPosX - enemyPosX);
			bool bShouldwait = false;

			// Detect right head
			if (firstEnemyRight < 0 && enemyPosX > playerPosX)	// If first enemy is not set, use first index if right side of player
			{
				firstEnemyRight = i;
			}
			else if (enemyPosX > playerPosX && enemyDistToPlayer < FMath::Abs(playerPosX - enemies[firstEnemyRight]->GetActorLocation().X))	// if enemy is to right and distance is closer than firstEnemy
			{				
				enemies[firstEnemyRight]->bIsHead = false;	// last first enemy is not first anymore
				firstEnemyRight = i;						// This is new the index for new first enemy
				enemies[firstEnemyRight]->bIsHead = true;	// set head for new first enemy
				//UE_LOG(LogTemp, Warning, TEXT("Found new Right head...."));
			}

			// Detect left head
			if (firstEnemyLeft < 0 && enemyPosX < playerPosX)
			{
				firstEnemyLeft = i;
			}
			else if (enemyPosX < playerPosX && enemyDistToPlayer < FMath::Abs(playerPosX - enemies[firstEnemyLeft]->GetActorLocation().X))
			{				
				enemies[firstEnemyLeft]->bIsHead = false;
				firstEnemyLeft = i;
				enemies[firstEnemyLeft]->bIsHead = true;
				//UE_LOG(LogTemp, Warning, TEXT("Found new Left head...."));
			}

			// Make each enemy behind head wait
			for (int32 j = 0; j < enemyCount; j++)
			{
				if (!IsValid(enemies[j])) break;
				float otherEnemyPosX = enemies[j]->GetActorLocation().X;
				float otherEnemyDistToPlayer = FMath::Abs(playerPosX - otherEnemyPosX);

				// if not comparing with self
				if (otherEnemyPosX != enemyPosX)
				{
					// if compared enemies are on same side of player
					if ((enemyPosX > playerPosX && otherEnemyPosX > playerPosX) || (enemyPosX < playerPosX && otherEnemyPosX < playerPosX))
					{
						// if enemy is further from player than other enemy (we do not need to stop enemy that is in front of compared enemy)
						if (enemyDistToPlayer > otherEnemyDistToPlayer)
						{
							// if enemy is less than 60cm apart
							if (FMath::Abs(otherEnemyPosX - enemyPosX) < enemyGap)
							{
								bShouldwait = true;
								//UE_LOG(LogTemp, Warning, TEXT("Waiting...."));
							}
						}
					}
				}
				enemies[i]->bIsWaiting = bShouldwait;
			}
		}
		else
		{
			enemies.RemoveAt(i, 1, true); // remove missing/destroyed element
			enemyCount--;
			i--; // removing shrinks array by one so we need to check same element again on next loop
		}
	}

	//// Debug stuff below if problems occur
	//if (enemies.Num()> 0 && firstEnemyLeft >= 0)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("First enemy LEFT is %s"), *enemies[firstEnemyLeft]->GetName());
	//}

	//if (enemies.Num() > 0 && firstEnemyRight >= 0)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("First enemy RIGHT is %s"), *enemies[firstEnemyRight]->GetName());
	//}

	//for (int32 t = 0; t < enemies.Num(); t++)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Enemies left: %s"), *enemies[t]->GetName());
	//}
}

void ADemoGameBase::SpawnEnemy()
{

	if (enemies.Num() >= maxEnemies) return;
	id = Increment(id);
	enemyCount = Increment(enemyCount);
	///spawn parameters to enforce uniqueness
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Name = FName(*Entityname(FString("Enemy"), id));

	UClass *a = EnemyFetcher(); ///Fetch enemy prefab
	AEnemy2D *b = GetWorld()->SpawnActor<AEnemy2D>(a, FVector::ZeroVector, FRotator(0.0f, 90.0f, 0.0f), SpawnInfo);
	
	if (b)
	{
		b->Rename(*Entityname(FString("Enemy"), id));
		b->Tags.Add("Enemy");
		b->audioPlayer = audioPlayer;
		enemies.Add(b);
	}
}


/*debugger which includes GEngine
@param Level is priority of message,
@param disp is a value that you need to be displayed
*/
void ADemoGameBase::Debugger(int level = 0, int disp = 0, FString message = " ")
{
	FString temp;
	temp.AppendInt(disp);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(level, 5.f, FColor::Yellow, message + "  " + temp);
	}
}

void ADemoGameBase::EnemyListRemover(AEnemy2D *enemy)
{
	enemies.Remove(enemy);
}

//event handler for player death
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

//Enemy prefab picker
UClass *ADemoGameBase::EnemyFetcher()
{
	cumulative = 0.0f;
	diceRoll = FMath::RandRange(0.0f, 100.0f);
	for (int i = 0; i < EnemyPrefabs.Num(); i++)
	{
		cumulative += chances[i];

		if (diceRoll <= cumulative)
		{
			return EnemyPrefabs[i];
		}
	}

	return nullptr;
}
