// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScoreManager.generated.h"

/**
 * 
 */

static uint64 CurrentScore = 0ULL;
static uint64 SessionHighScore = 0ULL;

UCLASS()
class CPPTEST_API UScoreManager : public UObject
{
	GENERATED_BODY()
	
public:
	UScoreManager() {}
	~UScoreManager() {}

	static void AddPoints(int points);
	static void ResetCurrentScore();
	static uint64 GetSessionHighScore();
	static void EndSession();

};
