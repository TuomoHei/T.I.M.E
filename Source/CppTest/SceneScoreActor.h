// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneScoreActor.generated.h"

UCLASS()
class CPPTEST_API ASceneScoreActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneScoreActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddPoints(int points);
	void ResetCurrentScore();

	UPROPERTY(BlueprintReadOnly, Category = "Score Management/Scene Score Actor")
		float MultiplierTimer;

	UPROPERTY(BlueprintReadOnly, Category = "Score Management/Scene Score Actor")
		int ScoreMultiplier;

private:
	bool bIsPaused;
	int CurrentScore;
	const float MultiplierTimerAddition = 5.0f;
	
};
