// Fill out your copyright notice in the Description page of Project Settings.

#include "TestPlayerController.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Player2D.h"
#include "Enemy2D.h"
#include "DemoGameBase.h"
#include "Item.h"
#include "TimerManager.h"

#if !UE_BUILD_SHIPPING
#include "Runtime/Engine/Public/DrawDebugHelpers.h" //for debug
bool runDebug = true;
#else
bool runDebug = false;
#endif


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
	float val = RegPlayer2D->pickUpRange;
	FHitResult *hit = new FHitResult();
	GetHitResultUnderFingerByChannel(FingerIndex, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, *hit);

	if (!hit) return;

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
		if (AttackEnemy(hit, WeaponCheck(*hit))) return;

		///pickup hit 
		if (IsValid(Cast<AItem>(hit->GetActor())) && !RegPlayer2D->item)
		{
			if (!hit->GetActor()->GetAttachParentActor())
				RegPlayer2D->PickUp(hit->GetActor());
		}
	}

	if (FMath::Abs((hit->ImpactPoint - RegPlayer2D->GetActorLocation()).X) <= RegPlayer2D->moveRange)
	{
		HitPos = hit->ImpactPoint;
		if (runDebug)
			DrawDebugPoint(GetWorld(), hit->ImpactPoint, 8000, FColor(255, 0, 0), true, 3.0f);
	}
}

bool ATestPlayerController::WeaponCheck(FHitResult hit)
{
	if (!RegPlayer2D->item)return false;

	if (RegPlayer2D->item->IsActorBeingDestroyed()) return false;
	Cast<AItem>(RegPlayer2D->item)->UseWeapon(IsValid(Cast<AEnemy2D>(hit.GetActor())));
	return IsValid(Cast<AItem>(RegPlayer2D->item)) && !Cast<AItem>(RegPlayer2D->item)->meleeweapon;
}

bool ATestPlayerController::AttackEnemy(FHitResult *hit, bool rangedweapon)
{
	if (!rangedweapon)
	{
		ADemoGameBase::Debugger(123, 0, hit->GetActor()->GetName());
		if (!IsValid(Cast<AEnemy2D>(hit->GetActor())))return false;
		///Delegate for the timer (Attacktime can be assigned via player BP
		FTimerDelegate a = FTimerDelegate::CreateLambda([=](void)
		{
			RegPlayer2D->AttackEnemy(hit->GetActor());
		});

		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, a, RegPlayer2D->attackTime, false);

		if (runDebug)
			DrawDebugPoint(GetWorld(), hit->ImpactPoint, 5000, FColor(0, 255, 0), false, 3.0f);

		RegPlayer2D->bIsAttacking = true;
		return true;
	}
	return false;
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
	if (timeManager&& runDebug)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time Manipulator found"));
	}
}
