// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Public/Tickable.h"
#include "ScoreManager.generated.h"

/**
 * 
 */

static uint64 CurrentScore = 0ULL;
static uint64 SessionHighScore = 0ULL;
static float MultiplierTimer;
static const float MultiplierTimerAddition = 5.0f;
static int ScoreMultiplier;
static bool IsPaused;

UCLASS()
class CPPTEST_API UScoreManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UScoreManager();
	~UScoreManager() {}

	void Tick(float DeltaTime) override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;

	static void AddPoints(int points);
	static void ResetCurrentScore();
	static uint64 GetSessionHighScore();
	static void EndSession();

};
