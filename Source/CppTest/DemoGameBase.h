// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "DemoGameBase.generated.h"



UCLASS()
class CPPTEST_API ADemoGameBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	static void Debugger(int level, int disp, FString message);
	void OnPlayerDeath();
	TSubclassOf<class AEnemy2D> EnemyPrefab;

private:

	ADemoGameBase();
	void StartPlay() override;
	void CheckLevel();
	void EndLevel();
	void SpawnEnemy();
	void Tick(float DeltaSeconds) override;
	const float timerValue = 5.0f;
	int id;


	class AActor *enemy;
	float timer = 6;
	int32 enemyCount;
	TArray<FVector> EnemySpawns;

	UPROPERTY(EditAnywhere, Category = "EnemySpawn")
		int32 Spawnrate = 5;

	int32 currentLevelIndex;
	class APlayerController *Controller;
};
