// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreManager.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

UScoreManager::UScoreManager()
{
	MultiplierTimer = 0.0f;
	ScoreMultiplier = 1;
	IsPaused = false;
}

void UScoreManager::Tick(float DeltaTime)
{
	if (!IsPaused && MultiplierTimer > 0.0f)
	{
		MultiplierTimer -= DeltaTime;

		if (MultiplierTimer < 0.0f)
		{
			if (ScoreMultiplier > 2)
			{
				MultiplierTimer = MultiplierTimerAddition;
			}
			else
			{
				MultiplierTimer = 0.0f;
			}
			ScoreMultiplier--;
		}
	}

	GEngine->AddOnScreenDebugMessage(1336, 5.0f, FColor::White, FString::Printf(TEXT("Score multiplier: %i"), ScoreMultiplier));
	GEngine->AddOnScreenDebugMessage(1337, 5.0f, FColor::White, FString::Printf(TEXT("Current time: %f"), MultiplierTimer));
}

bool UScoreManager::IsTickableInEditor() const
{
	return false;
}

bool UScoreManager::IsTickableWhenPaused() const
{
	return false;
}

TStatId UScoreManager::GetStatId() const
{
	return TStatId();
}

void UScoreManager::AddPoints(int points)
{
	CurrentScore += (uint64)FMath::Abs(points * ScoreMultiplier++);
	MultiplierTimer = MultiplierTimerAddition;
	GEngine->AddOnScreenDebugMessage(69, 5.0f, FColor::Green, FString::Printf(TEXT("Current score: %i"), CurrentScore));
}

void UScoreManager::ResetCurrentScore()
{
	CurrentScore = 0ULL;
	MultiplierTimer = 0.0f;
	ScoreMultiplier = 1;
}

uint64 UScoreManager::GetSessionHighScore()
{
	return SessionHighScore;
}

void UScoreManager::EndSession()
{
	SessionHighScore = CurrentScore;
	ResetCurrentScore();

	/*
	Temporary pseudo-code: Submit SessionHighScore to Google Play.
	gpg::LeaderboardManager.SubmitScore(leaderboard_id, SessionHighScore);
	*/
}
