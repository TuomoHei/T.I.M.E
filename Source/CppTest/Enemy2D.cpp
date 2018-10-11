// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy2D.h"

// Sets default values
AEnemy2D::AEnemy2D()
{
	PrimaryActorTick.bCanEverTick = true;




	if (!RootComponent)
	{
		C_rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyRoot"));
		RootComponent = C_rootBox;
	}

	walkSpeed = 20.0f;
	maxDistance = 100.0f;
	state = CB_walking;

}

AEnemy2D::~AEnemy2D()
{

}

// Called when the game starts or when spawned
void AEnemy2D::BeginPlay()
{
	bGameEnd = false;
	Super::BeginPlay();
}

void AEnemy2D::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

}

// Called every frame
void AEnemy2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bGameEnd)
	{
		AEnemy2D::Movement(walkSpeed, DeltaTime);
	}
}

void AEnemy2D::Movement(float moveValue, float Deltatime)
{
	///variables for calculating distance between this object and player

	///ADD overlapping prevention
	FVector newLoc = GetActorLocation();
	FVector b = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector temp = b - GetActorLocation();
	temp.Normalize();
	ADemoGameBase::Debugger(10, GetActorLocation().X, FString("CurrentX : "));
	ADemoGameBase::Debugger(100, FVector::Distance(GetActorLocation(), b), FString("Distance "));

	///Distance checker
	if (FMath::Abs(FVector::Distance(GetActorLocation(), b)) > maxDistance)
	{
		if (state != CB_walking) state = CB_walking;
	}
	else
	{
		if (state != CB_fighting) state = CB_fighting;
	}

	if (state == CB_walking)
	{
		newLoc.X += temp.X * Deltatime * moveValue;
		SetActorLocation(newLoc);
	}
	else
	{
		///combat logic here

	}
}

///put more content relating to game ending on player death 
void AEnemy2D::PlayerDeath()
{
	bGameEnd = true;
	ADemoGameBase::Debugger(10, 0, FString("ENEMIII KILLED"));
}
