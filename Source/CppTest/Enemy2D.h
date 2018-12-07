// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "AudioPlayer.h"
#include "Enemy2D.generated.h"

static int indexWep = 0;

UENUM()
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
		void AddWeapon(int index);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BPClasses)
		UClass *weaponPrefab;
	UPROPERTY(BlueprintReadOnly)
		bool bIsWaiting = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsStaggering = false;
	UPROPERTY()
		bool bIsHead = false;
	UFUNCTION(BlueprintCallable)
		void TakeDamageEnemy(bool weapon);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<CombatState> state;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AItem *item;
	class AItem *item2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AAudioPlayer *audioPlayer;

protected:

	class ATestPlayerController *controller;
	TArray<AActor*> player;
	TArray<AActor*> scoreActor;
	float timer;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Movement(float moveValue, float Deltatime);
	UPROPERTY(EditAnywhere, Category = "Movement")
		float walkSpeed;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float maxDistance;
	UPROPERTY(VisibleAnywhere, Category = "Exterior")
		class UBoxComponent *C_rootBox;
};

