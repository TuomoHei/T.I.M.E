// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TimeManager.h"
#include "DemoPlayer.generated.h"

UCLASS()
class CPPTEST_API ADemoPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADemoPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input 
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:
	//Input variables
	FVector2D MovementInput;

	float Speed;
	float OldSpeed;
	ATimeManager* pTimeManager;
private:
	//Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void ChangeSlow();
	void ChangeNormal();
};
