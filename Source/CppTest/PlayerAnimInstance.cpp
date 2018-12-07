// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "GameFramework/Actor.h"
#include "Player2D.h"
#include "EngineUtils.h"
#include "Item.h"
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
	//float moveX = PlayerClass->BulletDirection.X;
	//UE_LOG(LogTemp, Warning, TEXT("move X %f"), moveX);
		
	if (FMath::Abs(moveX) >= 2)
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
	//if (bIsAttacking)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("attacking"));
	//}

	AItem *item = Cast<AItem>(PlayerClass->item);	// todo: can optimize with local hasWeapon bool in player and check only that bool instead of casting every frame	

	if (item != nullptr)
	{
		if (item->meleeweapon && bIsAttacking)
		{
			bIsMeleeing = true;
			//UE_LOG(LogTemp, Warning, TEXT("is meleeing = true"));
		}
		else if (!item->meleeweapon)
		{
			bIsShooting = true;
			//UE_LOG(LogTemp, Warning, TEXT("Shooting"));
		}
	}
	else
	{
		bIsShooting = false;
		bIsMeleeing = false;
	}

	// ** Dying **
	bIsAlive = PlayerClass->canMove;
}

void UPlayerAnimInstance::SetAttackAnimID()
{
	attackAnimID = rand() % attackAnims.Num();	
	//if (PlayerClass) { PlayerClass->bIsAttacking = false; }
	//attackAnims[attackAnimID]->GetPlayLength();
}

float UPlayerAnimInstance::SetAttackDuration()
{
	float dur = attackAnims[attackAnimID]->GetPlayLength();
	if (PlayerClass) { PlayerClass->attackTime = dur; }
	else { UE_LOG(LogTemp, Warning, TEXT("Player class is NULL")); }
	return dur;
}

float UPlayerAnimInstance::GetAttackDuration()
{
	return attackAnims[attackAnimID]->GetPlayLength();
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




