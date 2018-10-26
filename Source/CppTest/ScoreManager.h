// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScoreManager.generated.h"

/**
 * 
 */

UCLASS()
class CPPTEST_API UScoreManager : public UObject
{
	GENERATED_BODY()
	
public:
	void AddPoints(int points);
	void ResetCurrentScore();
	uint64 GetSessionHighScore();
	void EndSession();

private:
	UScoreManager();
	~UScoreManager();

	uint64 CurrentScore;
	uint64 SessionHighScore;

};
