// Fill out your copyright notice in the Description page of Project Settings.

#include "TestPlayerController.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Player2D.h"
#include "Enemy2D.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h" //for debug
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

	if (FMath::Abs((hit->ImpactPoint - RegPlayer2D->GetActorLocation()).X) <= RegPlayer2D->pickUpRange)
	{
		if (IsValid(Cast<AEnemy2D>(hit->GetActor())))
		{
			if (IsValid(RegPlayer2D->ItemGetter()))
			{
				if (!Cast<AItem>(RegPlayer2D->ItemGetter())->meleeweapon)
					return;
			}


			///Delegate for the timer (Attacktime can be assigned via player BP
			FTimerDelegate a = FTimerDelegate::CreateLambda([=](void)
			{
				RegPlayer2D->AttackEnemy(hit->GetActor());
			});

			FTimerHandle handle;
			GetWorldTimerManager().SetTimer(handle, a, RegPlayer2D->attackTime, false);
			DrawDebugPoint(GetWorld(), hit->ImpactPoint, 50, FColor(0, 255, 0), false, 3.0f);

			RegPlayer2D->bIsAttacking = true;
			return;
		}

		if (hit->GetActor()->ActorHasTag(FName("PickUp")))
		{
			if (!hit->GetActor()->GetAttachParentActor())
				RegPlayer2D->PickUp(hit->GetActor());
		}
	}

	if (FMath::Abs((hit->ImpactPoint - RegPlayer2D->GetActorLocation()).X) <= RegPlayer2D->moveRange)
	{
		HitPos = hit->ImpactPoint;
		DrawDebugPoint(GetWorld(), hit->ImpactPoint, 50, FColor(255, 0, 0), false, 3.0f);
	}

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
	timeManager = RegPlayer2D->FindComponentByClass<UTimeManipulator>();
	if (timeManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time Manipulator found"));
	}
}
