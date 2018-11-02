// Fill out your copyright notice in the Description page of Project Settings.

#include "TestPlayerController.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Player2D.h"
#include "PickupComponent.h"
#include "Enemy2D.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h" //for debug
#include "DemoGameBase.h"
#include "Async.h"
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
	FHitResult hit;


	if (GetHitResultUnderFingerByChannel(FingerIndex, UEngineTypes::ConvertToTraceType(ECC_Camera), true, hit))
	{
		if ((hit.ImpactPoint - RegPlayer2D->GetActorLocation()).X <= RegPlayer2D->pickUpRange)
		{
			if (hit.GetActor()->ActorHasTag(FName("Enemy")))
			{
				FTimerDelegate a = FTimerDelegate::CreateLambda([=](void) {ADemoGameBase::Debugger(0, 0, FString("Called")); RegPlayer2D->AttackEnemy(hit.GetActor());  });
				FTimerHandle handle;
				GetWorldTimerManager().SetTimer(handle,a, RegPlayer2D->attackTime, false);

				return;
			}

			if (hit.GetActor()->ActorHasTag(FName("PickUp")))
			{
				RegPlayer2D->PickUp(hit.GetActor());
				return;
			}
		}

		if (FMath::Abs((hit.ImpactPoint - RegPlayer2D->GetActorLocation()).X) >= RegPlayer2D->moveRange) return;

			FVector temp;

			temp = hit.ImpactPoint;
			HitPos = temp;
			DrawDebugPoint(GetWorld(), hit.ImpactPoint, 20, FColor(255, 0, 0), false, 1.0f);
			ADemoGameBase::Debugger(175, (int)HitPos.X, FString("Hitpoint X value"));
	}
}

void ATestPlayerController::RegisterPlayer2D(APlayer2D *actor)
{
	RegPlayer2D = actor;
}
