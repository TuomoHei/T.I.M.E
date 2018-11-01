// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"	// needed for UGameplayStatics
#include "Gameframework/PlayerController.h"
#include "Player2D.h"
#include "EngineUtils.h"
#include <stdlib.h>	// Needed for rand
#include "DemoGameBase.h"	// debugging

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	UWorld* GameWorld = this->GetWorld();	

	// Find player
	for (TActorIterator<APlayer2D> Itr(GameWorld); Itr; ++Itr)
	{
		// Filter out objects not contained in the target world.
		if (Itr->GetWorld() != GameWorld)
		{
			continue;	// skip rest of loop
		}

		PlayerClass = *Itr;
		UE_LOG(LogTemp, Warning, TEXT("Found player object named: %s"), *PlayerClass->GetName());
	}

	// Get skeletal mesh
	skeletalMeshComp = PlayerClass->FindComponentByClass<USkeletalMeshComponent>();
	if (skeletalMeshComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Skeletal Mesh found"));
	}

	bIsAlive = true;	// set player alive

	GLog->Log("Initialized animation instance");
}

void UPlayerAnimInstance::UpdateAnimationProperties()
{
	if (PlayerClass)
	{
		//UE_LOG(LogTemp, Warning, TEXT("INPUT MOVE X:  %f"), PlayerClass->MovementInput.X);


		// ** Handle moving **

		float moveX = PlayerClass->MovementInput.X;
		
		if (moveX != 0)
		{
			bIsMoving = true;

			if (moveX > 0)
			{
				// Moves right
				skeletalMeshComp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
			}
			else if (moveX < 0)
			{
				// Moves left
				skeletalMeshComp->SetWorldScale3D(FVector(1.0f, -1.0f, 1.0f));
			}
		}
		else
		{
			bIsMoving = false;
		}

		// ** Attakcing **

		// ** Crouching ** 

		// ** Sliding **
		
		// ** Dying **
		//bIsAlive = PlayerClass-> // isAlive?

	}
}

void UPlayerAnimInstance::SetAttackAnimID()
{
	attackAnimID = rand() % 2;	// Set number to x-1 of x attack animations implemented
}


