// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "Enemy2D.h"
#include "Player2D.h"
#include "DemoGameBase.generated.h"

static auto Increment = [=](int a) { if (a > 100) return 0; else return a+1; };
static auto Entityname = [=](FString a, int b) { FString name; name.AppendInt(b); name += a; return name; };

UCLASS()
class CPPTEST_API ADemoGameBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	static void Debugger(int level, int disp, FString message);
	void OnPlayerDeath();
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = EnemySpawn)
		TArray<UClass*> EnemyPrefabs;
private:

	ADemoGameBase();
	void LoadEnemies();
	void StartPlay() override;
	void CheckLevel();
	void EndLevel();
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


	UPROPERTY()
		TArray<AEnemy2D*> enemies;

	UPROPERTY()
		APlayer2D* Player;
};
