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
	timer = timerValue;
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
}

void ADemoGameBase::CheckLevel()
{
	FString CurrentLevelName = GetWorld()->GetMapName();
}

void ADemoGameBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	timer -= DeltaSeconds;

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
	id = Increment(id);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Name = FName(*Entityname(FString("Enemy"), id));
	UClass *a = EnemyFetcher();
	a->Rename(*Entityname(FString("Enemy"), id));
	AEnemy2D *b =  GetWorld()->SpawnActor<AEnemy2D>(a, FVector::ZeroVector, FRotator(0.0f, 90.0f, 0.0f), SpawnInfo);
	b->Tags.Add("Enemy");
	b->Rename(*Entityname(FString("Enemy"),id));
}

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
