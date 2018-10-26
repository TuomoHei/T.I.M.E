// Fill out your copyright notice in the Description page of Project Settings.
#include "TestPlayerController.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Enemy2D.h"
#include "DemoGameBase.h"


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
				hit.GetActor()->Destroy();
			}

			if (hit.GetActor()->ActorHasTag(FName("PickUp")))
			{
				RegPlayer2D->PlayerPickUp(hit.GetActor());
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
