// Fill out your copyright notice in the Description page of Project Settings.
#include "TestPlayerController.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
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
		if (hit.Actor.Get()->Tags.Contains(FName("Player")))
		{
			FVector temp;

			temp = hit.ImpactPoint;
			HitPos = temp;
			DrawDebugPoint(GetWorld(), hit.ImpactPoint, 20, FColor(255, 0, 0), false, 1.0f);
			ADemoGameBase::Debugger(175, (int)HitPos.X, FString("Hitpoint X value"));

		}
	}
	//FVector worldLoc;
	//FVector worldDir;
	//float x;
	//float y;
	//bool b;

	//GetInputTouchState(FingerIndex, x, y, b);
	//DeprojectScreenPositionToWorld(x, y, worldLoc, worldDir);
	//HitPos = worldLoc;

}

void ATestPlayerController::RegisterPlayer2D(APlayer2D *actor)
{
	RegPlayer2D = actor;
}
