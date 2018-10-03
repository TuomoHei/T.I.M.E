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
	UStaticMeshComponent *C_enemyMesh;

	C_enemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemymesh"));
	C_enemyMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemymeshAsset(TEXT("/Game/Cube.Cube"));
	if (EnemymeshAsset.Succeeded())
	{
		C_enemyMesh->SetStaticMesh(EnemymeshAsset.Object);
		C_enemyMesh->SetWorldScale3D(FVector(0.8f));
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

	if (FMath::Abs(FVector::Distance(GetActorLocation(), b)) > maxDistance)
	{
		if (state != CB_walking) state = CB_walking;

		if (state == CB_walking)
		{
			newLoc.Y += temp.Y * Deltatime * moveValue;
			SetActorLocation(newLoc);
		}
	}
	else
	{
		if (state != CB_fighting) state = CB_fighting;
		///combat logic here
	}
}

///put more content relating to game ending on player death 
void AEnemy2D::PlayerDeath()
{
	bGameEnd = true;
	ADemoGameBase::Debugger(10, 0, FString("ENEMIII KILLED"));
}

