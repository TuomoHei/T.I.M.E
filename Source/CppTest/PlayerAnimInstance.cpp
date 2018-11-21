// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "GameFramework/Actor.h"
#include "Player2D.h"
#include "EngineUtils.h"
#include <stdlib.h>	// Needed for rand

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Find player class
	PlayerClass = GetPlayerClass();

	// Get skeletal mesh component
	skeletalMeshComp = GetSkeletalMeshComp();
	
	bIsAlive = true;
	bIsMoving = false;	

	if (PlayerClass != nullptr)
	{
		SetAttackAnimID();	// Set initial attack anim and feed length to player
	}	
}

void UPlayerAnimInstance::UpdateAnimationProperties()
{
	if (!PlayerClass)
		return;	
	
	// ** Moving **
	float moveX = PlayerClass->MovementInput.X;		
	if (moveX != 0)
	{
		bIsMoving = true;

		if (moveX > 0 && skeletalMeshComp)
		{
			// Moves right
			skeletalMeshComp->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
		}
		else if (moveX < 0 && skeletalMeshComp)
		{
			// Moves left
			skeletalMeshComp->SetWorldScale3D(FVector(1.0f, -1.0f, 1.0f));
		}
	}
	else
	{
		bIsMoving = false;
	}

	// ** Attacking **
	bIsAttacking = PlayerClass->bIsAttacking;

	// ** Crouching ** 

	// ** Sliding **
		
	// ** Dying **
	//bIsAlive = PlayerClass-> // isAlive?	
}

void UPlayerAnimInstance::SetAttackAnimID()
{
	attackAnimID = rand() % attackAnims.Num();	
	PlayerClass->bIsAttacking = false;
	GetAttackDuration();	
}

float UPlayerAnimInstance::GetAttackDuration()
{
	float dur = attackAnims[attackAnimID]->GetPlayLength();	
	PlayerClass->attackTime  = dur;
	return dur;
}

// Find and return player class
APlayer2D* UPlayerAnimInstance::GetPlayerClass()
{
	UWorld* GameWorld = this->GetWorld();
	APlayer2D *player = 0;

	// Find player
	for (TActorIterator<APlayer2D> Itr(GameWorld); Itr; ++Itr)
	{
		// Filter out objects not contained in the target world.
		if (Itr->GetWorld() != GameWorld)
		{
			continue;	// skip rest of loop
		}

		player = *Itr;
	}
	
	return player;
}

// Get skeletal mesh component from player
USkeletalMeshComponent* UPlayerAnimInstance::GetSkeletalMeshComp()
{
	USkeletalMeshComponent* skeleMesh = 0;

	if (PlayerClass)
	{
		skeleMesh = PlayerClass->FindComponentByClass<USkeletalMeshComponent>();
		if (skeleMesh != 0)
		{
			UE_LOG(LogTemp, Display, TEXT("Player Skeletal Mesh found"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning: Player NOT FOUND!"));
	}

	return skeleMesh;
}




