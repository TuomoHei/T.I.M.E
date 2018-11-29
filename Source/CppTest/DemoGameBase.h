// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "AudioPlayer.h"
#include "DemoGameBase.generated.h"

//Increase the number by one /w safe proof
static auto Increment = [](int a) { if (a > 500 )return 0; else return a + 1;};

//give name to the entity
static auto Entityname = [](FString a, int b) { FString name; name.AppendInt(b); name += a; return name; };

static auto Movevalue = [](FVector moveVector) {
	if (moveVector.X > 0) return 1;
	else if (moveVector.X < 0) return -1;
	else return 0;
};

UCLASS()
class CPPTEST_API ADemoGameBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	int32 enemyCount;
	//debugger with GE engine
	static void Debugger(int level, int disp, FString message);
	void EnemyListRemover(class AEnemy2D *enemy);
	//Global method for player death event
	void OnPlayerDeath();
	//List containing enemyprefabs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EnemySpawn)
		TArray<UClass*> EnemyPrefabs;

	UPROPERTY(EditAnywhere)
		float enemyGap = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		AAudioPlayer *audioPlayer;
	
private:

	ADemoGameBase();
	~ADemoGameBase();
	void StartPlay() override;
	void SpawnEnemy();
	void Tick(float DeltaSeconds) override;

	const float timerValue = 5.0f;
	int id;
	float diceRoll;
	float cumulative;
	float timer = 6;
	int32 currentLevelIndex;
	TArray<FVector> EnemySpawns;
	UClass* EnemyFetcher();
	class APlayerController *Controller;

	UPROPERTY(EditDefaultsOnly, Category = "EnemySpawn")
		float chances[3];
	UPROPERTY(EditDefaultsOnly, Category = "EnemySpawn")
		int32 Spawnrate;
	UPROPERTY(EditDefaultsOnly, Category = "EnemySpawn")
		int maxEnemies;
	UPROPERTY()
		TArray<class AEnemy2D*> enemies;
	UPROPERTY()
		class APlayer2D* Player;
};
