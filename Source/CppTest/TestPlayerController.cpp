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


		if (FMath::Abs((hit->ImpactPoint - RegPlayer2D->GetActorLocation()).X) <= RegPlayer2D->pickUpRange)
		{
			if (hit->GetActor()->ActorHasTag(FName("Enemy")))
			{
				///Delegate for the timer (Attacktime can be assigned via player BP
				FTimerDelegate a = FTimerDelegate::CreateLambda([=](void) 
				{
					RegPlayer2D->AttackEnemy(hit->GetActor());  
				});

				FTimerHandle handle;
				GetWorldTimerManager().SetTimer(handle, a, RegPlayer2D->attackTime, false);
				DrawDebugPoint(GetWorld(), hit->ImpactPoint, 25, FColor(0, 255, 0), false, 1.0f);

			}

			if (hit->GetActor()->ActorHasTag(FName("PickUp")))
			{
				if(!hit->GetActor()->GetAttachParentActor())
				RegPlayer2D->PickUp(hit->GetActor());
			}
		}

		if (FMath::Abs((hit->ImpactPoint - RegPlayer2D->GetActorLocation()).X) <= RegPlayer2D->moveRange)
		{
			HitPos = hit->ImpactPoint;
			DrawDebugPoint(GetWorld(), hit->ImpactPoint, 10, FColor(255, 0, 0), false, 1.0f);
		}
	
}

void ATestPlayerController::RegisterPlayer2D(APlayer2D *actor)
{
	RegPlayer2D = actor;
}
