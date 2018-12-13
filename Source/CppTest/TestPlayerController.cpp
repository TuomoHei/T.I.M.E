// Fill out your copyright notice in the Description page of Project Settings.

#include "TestPlayerController.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Player2D.h"
#include "Enemy2D.h"
#include "DemoGameBase.h"
#include "Item.h"
#include "TimerManager.h"




void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	GetTimeManipulator();
}

void ATestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent)
		InputComponent->BindTouch(IE_Pressed, this, &ATestPlayerController::Touched);

}

void ATestPlayerController::Touched(ETouchIndex::Type FingerIndex, FVector location)
{
	if (!RegPlayer2D->canMove) return;

	float val = RegPlayer2D->pickUpRange;
	FHitResult *hit = new FHitResult();
	GetHitResultUnderFingerByChannel(FingerIndex, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, *hit);
	RegPlayer2D->AbleToMove = false;
	if (!hit) return;

	HitPos = hit->ImpactPoint;
	//timeManager->DeactivateSlowmotion();

	if (hit->GetActor() == NULL)
	{
		timeManager->DeactivateSlowmotion();
		return;
	}
	else
	{
		timeManager->DeactivateSlowmotionPermanent();
	}
	if (IsValid(RegPlayer2D->item)) val *= 2;

	if (FMath::Abs((hit->ImpactPoint - RegPlayer2D->GetActorLocation()).X) <= val)
	{
		///enemy hit
		if (AttackEnemy(hit, WeaponCheck(*hit)))
		{
			return;
		}

		///pickup hit 
		if (IsValid(Cast<AItem>(hit->GetActor())) && !RegPlayer2D->item)
		{
			if (IsValid(hit->GetActor()) && !hit->GetActor()->GetAttachParentActor())
				RegPlayer2D->PickUp(hit->GetActor());
		}
	}

	if (FMath::Abs((hit->ImpactPoint - RegPlayer2D->GetActorLocation()).X) <= RegPlayer2D->moveRange)
	{
		RegPlayer2D->AbleToMove = true;

	}
}

bool ATestPlayerController::WeaponCheck(FHitResult hit)
{
	if (!RegPlayer2D->item)return false;

	if (RegPlayer2D->item->IsActorBeingDestroyed()) return false;
	RegPlayer2D->Movement();
	Cast<AItem>(RegPlayer2D->item)->UseWeapon(IsValid(Cast<AEnemy2D>(hit.GetActor())),RegPlayer2D->BulletDirection);
	return IsValid(Cast<AItem>(RegPlayer2D->item)) && !Cast<AItem>(RegPlayer2D->item)->meleeweapon;
}

bool ATestPlayerController::AttackEnemy(FHitResult *hit, bool rangedweapon)
{
	if (!rangedweapon)
	{
		if (!IsValid(Cast<AEnemy2D>(hit->GetActor())))return false;
		///Delegate for the timer (Attacktime can be assigned via player BP
		FTimerDelegate a = FTimerDelegate::CreateLambda([=](void)
		{
			RegPlayer2D->AttackEnemy(hit->GetActor());
		});

		FTimerHandle handle;
		float attackTime = RegPlayer2D->attackTime - 0.25f;
		GetWorldTimerManager().SetTimer(handle, a, attackTime, false);
		//GetWorldTimerManager().SetTimer(handle, a, RegPlayer2D->attackTime, false);



		RegPlayer2D->bIsAttacking = true;
		return true;
	}
	return true;
}

void ATestPlayerController::RegisterPlayer2D(APlayer2D *actor)
{
	RegPlayer2D = actor;
}

void ATestPlayerController::RegisterGameBase(ADemoGameBase *base)
{
	RegGameBase = base;
}

void ATestPlayerController::GetTimeManipulator()
{
	if (!RegPlayer2D) return;
	timeManager = RegPlayer2D->FindComponentByClass<UTimeManipulator>();
	if (timeManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time Manipulator found"));
	}
}
