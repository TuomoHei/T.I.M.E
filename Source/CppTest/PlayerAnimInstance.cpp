// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"	// needed for UGameplayStatics
#include <stdlib.h>	// Needed for rand

#include "DemoGameBase.h"	// debugging

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//Cache pawn
	Player = TryGetPawnOwner(); // todo: not working

	//bIsAlive = true;
	GLog->Log("Initialized animation instance");
}

void UPlayerAnimInstance::UpdateAnimationProperties()
{
	ADemoGameBase::Debugger(0, 0, FString("ASasaSasSA"));

	APawn* Pawn = TryGetPawnOwner();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);	// Another way to get player
	if (PlayerController)
	{
		//bIsAlive = true;
		ADemoGameBase::Debugger(0, 0, FString("TESTING"));
	}

	if (Pawn)
	{
		//ADemoGameBase::Debugger(0, 0, FString("TESTING"));
	}

	if (Player)
	{
		// ads
		bIsAlive = true;
	}
}

void UPlayerAnimInstance::SetAttackAnimID()
{
	attackAnimID = rand() % 2;	// Set number to x-1 of x attack animations implemented
}
