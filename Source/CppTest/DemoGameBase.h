// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Enemy2D.h"
#include "Player2D.h"
#include <functional>
#include <list>
#include "Engine.h"
#include "DemoGameBase.generated.h"

UCLASS()
class CPPTEST_API ADemoGameBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	static void Debugger(int level, int disp, FString message);

private:

	ADemoGameBase();
	void StartPlay() override;
	void CheckLevel();
	void EndLevel();
	void SpawnEnemy();
	void OnPlayerDeath();
	void Tick(float DeltaSeconds) override;
	const float timerValue = 5.0f;
	int id;

	UPROPERTY(VisibleAnywhere, Category = "EnemySpawn")
		float timer = 6;
	UPROPERTY(VisibleAnywhere, Category = "EnemySpawn")
		int32 enemyCount;
	UPROPERTY(VisibleAnywhere, Category = "EnemySpawn")
		TArray<FVector> EnemySpawns;
	UPROPERTY(EditAnywhere, Category = "EnemySpawn")
		int32 Spawnrate = 5;

	int32 currentLevelIndex;
	APlayerController *Controller;
};
