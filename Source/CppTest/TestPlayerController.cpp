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
	FVector2D a;
	

	if (GetHitResultUnderFingerByChannel(FingerIndex, ETraceTypeQuery::TraceTypeQuery1, false, hit))
	{
		FVector temp;
		ADemoGameBase::Debugger(175, (int)hit.ImpactPoint.X, FString("Hitpoint X value"));
		temp = hit.ImpactPoint;
		if (temp != FVector::ZeroVector)
			HitPos = temp;


	}

	//RegPlayer2D->MoveRight(HitPos.X - RegPlayer2D->GetActorLocation().X);

}

void ATestPlayerController::RegisterPlayer2D(APlayer2D *actor)
{
	RegPlayer2D = actor;
}


