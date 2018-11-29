// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "ScoreManager.generated.h"

/**
 * 
 */

static uint64 CurrentScore = 0ULL;
static uint64 SessionHighScore = 0ULL;
static float MultiplierTimer;
static const float MultiplierTimerAddition = 5.0f;
static int ScoreMultiplier;
static bool bIsPaused;

UCLASS()
class CPPTEST_API UScoreManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UScoreManager();
	~UScoreManager() {}

	static bool Paused();
	UFUNCTION(BlueprintCallable, Category = "Score Manager")
	static bool Paused(bool bPaused);

	static void AddPoints(int points);
	static uint64 GetSessionHighScore();

	UFUNCTION(BlueprintCallable, Category = "Score Manager")
	static void ResetCurrentScore();

	UFUNCTION(BlueprintCallable, Category = "Score Manager")
	static void EndSession();

private:
	void Tick(float DeltaTime) override;
	//bool IsTickableInEditor() const override;
	//bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;

};
