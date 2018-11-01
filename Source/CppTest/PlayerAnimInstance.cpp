// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"	// needed for UGameplayStatics
#include "GameFramework/Actor.h"
#include "Gameframework/PlayerController.h"
#include "Player2D.h"
#include <stdlib.h>	// Needed for rand

#include "DemoGameBase.h"	// debugging

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	UWorld* GameWorld = this->GetWorld();	

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

	//skeletalMeshComp = PlayerClass->FindComponentByClass<USkeletalMeshComponent>();
	//skeletalMeshComp->GlobalAnimRateScale = 2.0f;

	bIsAlive = true;	// set player alive

	GLog->Log("Initialized animation instance");
}

void UPlayerAnimInstance::UpdateAnimationProperties()
{
	if (PlayerClass)
	{
		//UE_LOG(LogTemp, Warning, TEXT("INPUT MOVE X:  %f"), PlayerClass->MovementInput.X);

		float moveX = PlayerClass->MovementInput.X;
		
		if (moveX != 0)
		{
			bIsMoving = true;

			if (moveX > 0)
			{
				// Moves right
				
			}
			else if (moveX < 0)
			{
				// Moves left

			}
		}
		else
		{
			bIsMoving = false;
		}


	}
}

void UPlayerAnimInstance::SetAttackAnimID()
{
	attackAnimID = rand() % 2;	// Set number to x-1 of x attack animations implemented
}


