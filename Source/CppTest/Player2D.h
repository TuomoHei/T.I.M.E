// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UFUNCTION(BlueprintCallable)
		void PlayerDeath();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APlayer2D();
	bool bHoldingItem;
	void PlayerPickUp(AActor *targetObj);
	void DisEquip(AActor *targetObj);
	///Values for pickups and attack ranges
	UPROPERTY(EditAnywhere, Category = "Range")
		float moveRange;
	UPROPERTY(EditAnywhere, Category = "Range")
		float pickUpRange;

	class UBoxComponent *base;

	class ATestPlayerController *PC;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float axisValue);

	FVector MovementInput;


};
