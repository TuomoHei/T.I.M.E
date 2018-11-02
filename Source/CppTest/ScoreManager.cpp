// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreManager.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

void UScoreManager::AddPoints(int points)
{
	CurrentScore += (uint64)FMath::Abs(points);
	GEngine->AddOnScreenDebugMessage(69, 5.0f, FColor::Green, FString::Printf(TEXT("Current score: %i"), CurrentScore));
}

void UScoreManager::ResetCurrentScore()
{
	CurrentScore = 0ULL;
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
