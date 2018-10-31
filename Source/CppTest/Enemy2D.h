// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "Enemy2D.generated.h"

///Longest include is very path specific so if your unreal engine is located in other drive -> error

UCLASS()
class CPPTEST_API AEnemy2D : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy2D();
	~AEnemy2D();
	//takes care of actions that need to happen upon players death
	void PlayerDeath();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	bool bGameEnd;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float timerValue;

protected:
	enum CombatState
	{
		CB_walking, CB_fighting
	};

	class ATestPlayerController *controller;

	TArray<AActor*> player;
	CombatState state;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float walkSpeed;
	UFUNCTION(Category = "Movement")
		void Movement(float moveValue, float Deltatime);
	UPROPERTY(EditAnywhere, Category = "Combat")
		float maxDistance;

	float timer;
	UPROPERTY(VisibleAnywhere, Category = "Exterior")
		class UBoxComponent *C_rootBox;

};