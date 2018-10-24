// Fill out your copyright notice in the Description page of Project Settings.

#include "Player2D.h"
#include "TestPlayerController.h"
#include "DemoGameBase.h"
#include "Components/InputComponent.h"






// Sets default values
APlayer2D::APlayer2D()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	C_PBase = CreateDefaultSubobject<UBoxComponent>(TEXT("a"));
	RootComponent = C_PBase;
}

// Called when the game starts or when spawned
void APlayer2D::BeginPlay()
{
	Super::BeginPlay();

	InputComponent = NewObject<UInputComponent>(UInputComponent::StaticClass(), 
		TEXT("InputComponent"));
	SetupPlayerInputComponent(InputComponent);
	PC = Cast<ATestPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC)
	{
		PC->RegisterPlayer2D(this);
	}
}

// Called every frame
void APlayer2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bool bisCurPressed;
	if (!PC) return;
	PC->GetInputTouchState(ETouchIndex::Touch1, PC->newTouchLocation.X, PC->newTouchLocation.Y, bisCurPressed);

	if (FVector::Dist(GetActorLocation(), PC->HitPos) != 0)
	{
		FVector2D deltaTouchLocation = PC->newTouchLocation;
		FVector locationWorld;
		FVector directionWorld;
		PC->DeprojectScreenPositionToWorld(deltaTouchLocation.X, deltaTouchLocation.Y, locationWorld, directionWorld);

		deltaTouchLocation *= -1.0f;

		FVector deltaOffset = FVector(deltaTouchLocation.X, 0.0f, 0.0f);
		ADemoGameBase::Debugger(120, (int)(PC->HitPos.X - GetActorLocation().X), FString("Moving"));
		MovementInput = (FVector2D)deltaOffset;
		//Scale our movement input axis values by 100 units per second
		MovementInput = MovementInput.GetSafeNormal() * 100.0f;
		FVector NewLocation;
		NewLocation.X = FMath::Clamp(FVector::Distance(GetActorLocation(), locationWorld), 0.0f, 1.0f) * 20.0f;
		NewLocation.Y += MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void APlayer2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	//InputComponent->BindAxis("MoveRight", this, &APlayer2D::MoveRight);
}

void APlayer2D::MoveRight(float axisValue)
{
	MovementInput.X = FMath::Clamp<float>(axisValue, -1.0f, 1.0f);
}

void APlayer2D::PlayerDeath()
{
	ADemoGameBase::Debugger(100, 0, FString("Overlapping"));
	TArray<AActor*> gamemanager;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADemoGameBase::StaticClass(), gamemanager);
	ADemoGameBase *temp = Cast<ADemoGameBase>(temp[0].GetClass());
	temp->OnPlayerDeath();
}
