// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy2D.h"

// Sets default values
AEnemy2D::AEnemy2D()
{


 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy2D::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AEnemy2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

