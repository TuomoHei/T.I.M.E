// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Enemy2D.generated.h"

enum CombatState
{
	CB_walking, CB_fighting
};

UCLASS()
class CPPTEST_API AEnemy2D : public APawn
{
	GENERATED_BODY()

public:

	AEnemy2D();
	//takes care of actions that need to happen upon players death
	void PlayerDeath();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool bGameEnd;
	void StateChecker(float a, FVector b);

	UPROPERTY(EditAnywhere, Category = "Combat")
		float timerValue;
	UPROPERTY(BlueprintReadOnly)
		FVector direction;
	UFUNCTION(BlueprintImplementableEvent)
		void asdf(bool leftside);
	UFUNCTION(BlueprintCallable)
		void AddWeapon();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BPClasses)
		UClass *weaponPrefab;

	UPROPERTY()
		bool bIsWaiting = false;

protected:



	CombatState state;
	class ATestPlayerController *controller;
	TArray<AActor*> player;
	class AItem *item;
	int id;
	float timer;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Movement(float moveValue, float Deltatime);

	UFUNCTION(BlueprintImplementableEvent)
		void ShootEvent();
	UFUNCTION(BlueprintCallable)
		void Shoot();
	UPROPERTY(EditAnywhere, Category = "Movement")
		float walkSpeed;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float maxDistance;
	UPROPERTY(VisibleAnywhere, Category = "Exterior")
		class UBoxComponent *C_rootBox;
};