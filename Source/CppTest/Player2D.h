// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Player2D.generated.h"




UCLASS()
class CPPTEST_API APlayer2D : public APawn
{
	GENERATED_BODY()
		///IDLE, MOVEMENT,ATTACK Animation implementation needed

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class AActor *item;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void PlayerDeath();
	void AttackEnemy(AActor *enemy);
	void PickUp(AActor *targetObj);
	void UnEquip();
	APlayer2D();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	bool bHoldingItem;

	///Values for pickups and attack ranges
	UPROPERTY(EditAnywhere, Category = "Movement")
		float moveRange;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float moveSpeed;
	UPROPERTY(EditAnywhere, Category = "Attack")
		float pickUpRange;
	UPROPERTY(EditAnywhere, Category = "Attack")
		float attackTime;

	class UBoxComponent *base;

	class ATestPlayerController *PC;

	

	FVector MovementInput;

	
};
