// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Pawn.h"
#include "Player2D.generated.h"




UCLASS()
class CPPTEST_API APlayer2D : public APawn
{
	GENERATED_BODY()
		///IDLE, MOVEMENT,ATTACK

public:
	// Sets default values for this pawn's properties
	APlayer2D();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
		void PlayerDeath();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	class ATestPlayerController *PC;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveRight(float axisValue);

private:

	FVector MovementInput;

	UPROPERTY(EditAnywhere, Category = "Test")
		class UBoxComponent *C_PBase;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		class USpringArmComponent *SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		class UCameraComponent *Camera;

};
