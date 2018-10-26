// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreManager.h"

UScoreManager::UScoreManager()
{
	uint64 CurrentScore = 0ULL;
	uint64 SessionHighScore = 0ULL;
}

UScoreManager::~UScoreManager()
{
}

void UScoreManager::AddPoints(int points)
{
	CurrentScore += (uint64)FMath::Abs(points);
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
