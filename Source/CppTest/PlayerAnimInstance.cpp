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

	//Cache pawn
	//Player = TryGetPawnOwner(); // todo: not working

	UWorld* GameWorld = this->GetWorld();	

	// Get player
	//for (TObjectIterator<APlayer2D> Itr; Itr; ++Itr)
	//{
	//	// Filter out objects not contained in the target world.
	//	if (Itr->GetWorld() != GameWorld)
	//	{
	//		continue;	// skip rest of loop
	//	}

	//	PlayerClass = *Itr;
	//	UE_LOG(LogTemp, Warning, TEXT("Found UObject named: %s"), *PlayerClass->GetName());
	//	//UE_LOG(LogTemp, Warning, TEXT("TEST: %s"), PlayerClass->test);
	//}

	for (TActorIterator<APlayer2D> Itr(GameWorld); Itr; ++Itr)
	{
		// Filter out objects not contained in the target world.
		if (Itr->GetWorld() != GameWorld)
		{
			continue;	// skip rest of loop
		}

		PlayerClass = *Itr;
		UE_LOG(LogTemp, Warning, TEXT("Found UObject named: %s"), *PlayerClass->GetName());

		if (PlayerClass->test == 2)
		{
			UE_LOG(LogTemp, Warning, TEXT("TEST = %f"), PlayerClass->test);			
		}

	}

	bIsAlive = true;	// set player alive
	GLog->Log("Initialized animation instance AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
}

void UPlayerAnimInstance::UpdateAnimationProperties()
{
	//ADemoGameBase::Debugger(255, (int)PlayerClass->MovementInput.X, FString("Mooove X : "));

	//float xMove = PlayerClass->MovementInput.X;	// TODO make this work!
	//float xMove = PlayerClass->test;
	//UE_LOG(LogTemp, Warning, TEXT("INPUT MOVE X:  %f"), xMove);
	//UE_LOG(LogTemp, Warning, TEXT("INPUT MOVE X:  %f"), PlayerClass->MovementInput.X);

	//PlayerClass->MoveRight(-1.0f);

	if (PlayerClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("INPUT MOVE X:  %f"), PlayerClass->MovementInput.X);


		//bool hasWorld = this->ImplementsGetWorld();
		//UE_LOG(LogTemp, Warning, TEXT("HAS WORLDDDDDDDDDD =  %s"), hasWorld? TEXT("true") : TEXT("false"));		

		//bIsMoving = PlayerClass->MovementInput.X > 0 ? true : false;

		//if (xMove != 0)
		//{
		//	bIsMoving = true;
		//}
		//else
		//{
		//	bIsMoving = false;
		//}
		
		//ADemoGameBase::Debugger(255, (int)PlayerClass->MovementInput.X, FString("Move X : "));

		if (bIsMoving)
		{
			//GLog->Log("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA Movement INPUT: MOVING");
		}
		else
		{
			//GLog->Log("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA Movement INPUT: IDLE IDLE IDLE");
		}
	}
}

void UPlayerAnimInstance::SetAttackAnimID()
{
	attackAnimID = rand() % 2;	// Set number to x-1 of x attack animations implemented
}


