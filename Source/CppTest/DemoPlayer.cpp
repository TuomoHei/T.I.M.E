// Fill out your copyright notice in the Description page of Project Settings.

#include "DemoPlayer.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/WorldSettings.h"
#include "Engine/Classes/Engine/Engine.h"


// Sets default values
ADemoPlayer::ADemoPlayer()
	:MovementInput(FVector2D::ZeroVector)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Take control of the default Player (デフォルトプレイヤーをコントロール)
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ADemoPlayer::BeginPlay()
{
	Super::BeginPlay();
	SetupPlayerInputComponent(InputComponent);
	pTimeManager = ATimeManager::GetInstance(this);

	Speed = 0.0f;
	OldSpeed = 0.0f;
}

// Called every frame
void ADemoPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Handle movement based on our "MoveX" and "MoveY" axes
	if (!MovementInput.IsZero())
	{
		//Scale our movement input axis values by 100 units per second
		MovementInput = MovementInput.GetSafeNormal() * 100.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}
	
	OldSpeed = Speed;
	Speed = MovementInput.Size();

	// Detect change Speed
	if (Speed == 0.0f && OldSpeed != 0.0f)
	{
		ChangeSlow();
		//GEngine->AddOnScreenDebugMessage(
		//	-1,
		//	1.0f,
		//	FColor::Red,
		//	"ChangeSlow():"
		//);
	}
	else if (Speed != 0.0f && OldSpeed == 0.0f)
	{
		ChangeNormal();
		//GEngine->AddOnScreenDebugMessage(
		//	-1,
		//	1.0f,
		//	FColor::Red,
		//	"ChangeNormal():"
		//);
	}
}

// Called to bind functionality to input
void ADemoPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	GLog->Log("SetupPlayerInputComponent");


	//Hook up every-frame handling for our four axes
	InputComponent->BindAxis("MoveForward", this, &ADemoPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADemoPlayer::MoveRight);

	InputComponent->BindAction("Move", IE_Pressed, this, &ADemoPlayer::ChangeNormal);
}

void ADemoPlayer::MoveForward(float axisValue)
{
	MovementInput.X = FMath::Clamp<float>(axisValue, -1.0f, 1.0f);
}

void ADemoPlayer::MoveRight(float axisValue)
{
	MovementInput.Y = FMath::Clamp<float>(axisValue, -1.0f, 1.0f);
}

void ADemoPlayer::ChangeSlow()
{
	pTimeManager->StartSlow();
}

void ADemoPlayer::ChangeNormal()
{
	pTimeManager->StopSlow();
}

