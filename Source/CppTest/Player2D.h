// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Player2D.generated.h"

UCLASS()
class CPPTEST_API APlayer2D : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayer2D();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	FVector2D MovementInput;
private:
	void MoveRight(float axisValue);
	
};
