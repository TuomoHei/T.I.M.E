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
}




void ADemoGameBase::LoadEnemies()
{
	static ConstructorHelpers::FObjectFinder<UClass> UnarmedEnemyBlueprint(TEXT("Class'/Game/Blueprints/BP_UnarmedEnemy.BP_UnarmedEnemy_C'"));
	if (UnarmedEnemyBlueprint.Object)
	{
		EnemyPrefabs[0] = (UnarmedEnemyBlueprint.Object);

	}

	static ConstructorHelpers::FObjectFinder<UClass> MeleeEnemyBlueprint(TEXT("Class'/Game/Blueprints/BP_MeleeEnemy.BP_MeleeEnemy_C'"));
	if (MeleeEnemyBlueprint.Object)
	{
		EnemyPrefabs[1] = (MeleeEnemyBlueprint.Object);

	}

	static ConstructorHelpers::FObjectFinder<UClass> RangedEnemyBlueprint(TEXT("Class'/Game/Blueprints/BP_RangedEnemy.BP_RangedEnemy_C'"));
	if (RangedEnemyBlueprint.Object)
	{
		EnemyPrefabs[2]= (RangedEnemyBlueprint.Object);

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
	//int firstEnemy;
	int firstEnemyLeft = -1;
	int firstEnemyRight = -1;

	// Make enemy wait for enemies in front of him if condition are met.
	for (int32 i = 0; i < enemyCount; i++)
	{
		if (IsValid(enemies[i]))
		{
			float enemyPosX = enemies[i]->GetActorLocation().X;
			float enemyDistToPlayer = FMath::Abs(playerPosX - enemyPosX);
			bool bShouldwait = false;

			// detect right head
			if (firstEnemyRight < 0 && enemyPosX > playerPosX)
			{
				firstEnemyRight = i;
			}
			else if (enemyPosX > playerPosX && enemyDistToPlayer < FMath::Abs(playerPosX - enemies[firstEnemyRight]->GetActorLocation().X))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Found new Right head...."));
				firstEnemyRight = i;
			}

			// detect left head
			if (firstEnemyLeft < 0 && enemyPosX < playerPosX)
			{
				firstEnemyLeft = i;
			}
			else if (enemyPosX < playerPosX && enemyDistToPlayer < FMath::Abs(playerPosX - enemies[firstEnemyLeft]->GetActorLocation().X))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Found new Left head...."));
				firstEnemyLeft = i;
			}

			for (int32 j = 0; j < enemyCount; j++)
			{
				float otherEnemyPosX = enemies[j]->GetActorLocation().X;
				float otherEnemyDistToPlayer = FMath::Abs(playerPosX - otherEnemyPosX);

				// if not comparing with self
				if (otherEnemyPosX != enemyPosX)
				{
					// if compared enemies are on same side of player
					if ( (enemyPosX > playerPosX && otherEnemyPosX > playerPosX) || (enemyPosX < playerPosX && otherEnemyPosX < playerPosX))	
					{
						// if enemy is further from player than other enemy (we do not need to stop enemy that is in front of compared enemy)
						if (enemyDistToPlayer > otherEnemyDistToPlayer)
						{
							// if enemy is less than 60cm apart
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

	//// Debug stuff below
	//if (enemies.Num()> 0 && firstEnemyLeft >= 0)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("First enemy LEFT is %s"), *enemies[firstEnemyLeft]->GetName());
	//}

	//if (enemies.Num() > 0 && firstEnemyRight >= 0)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("First enemy RIGHT is %s"), *enemies[firstEnemyRight]->GetName());
	//}
}

void ADemoGameBase::SpawnEnemy()
{
	id = Increment(id);
	//if (id >= 6) return;

	FActorSpawnParameters SpawnInfo;
SpawnInfo.Name = FName(*Entityname(FString("Enemy"), id));
	UClass *a = EnemyFetcher();
	a->Rename(*Entityname(FString("Enemy"), id));
	AEnemy2D *b =  GetWorld()->SpawnActor<AEnemy2D>(a, FVector::ZeroVector, FRotator(0.0f, 90.0f, 0.0f), SpawnInfo);
	b->Tags.Add("Enemy");
	b->Rename(*Entityname(FString("Enemy"),id));}

void ADemoGameBase::EndLevel()
{
	FString LevelString = GetWorld()->GetMapName();
	FName LevelToLoad = FName(*LevelString);
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
	for (int i = 0; i < 3; i++)
	{
		cumulative += chances[i];

		if (diceRoll <= cumulative)
		{
			return EnemyPrefabs[i];
		}
	}

	return nullptr;
}
