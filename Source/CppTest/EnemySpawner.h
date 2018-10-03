// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy2D.h"
#include "EnemySpawner.generated.h"

UCLASS()
class CPPTEST_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnyWhere, Category = "SpawnSetteing")
		float RightEnd;
	UPROPERTY(EditAnyWhere, Category = "SpawnSetteing")
		float LeftEnd;
	UPROPERTY(EditAnyWhere, Category = "SpawnSetteing")
		float Interval;
	float Time;

	TSubclassOf<AActor> Enemy;
private:
	void SpawnTimer(float DeltaTime);
	void Spawn();
};
