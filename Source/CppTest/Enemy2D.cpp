// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy2D.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "UObjectGlobals.h"
#include "Player2D.h"
#include "DemoGameBase.h"
#include "PickupComponent.h"
#include "ScoreManager.h"

// Sets default values
AEnemy2D::AEnemy2D()
{
	PrimaryActorTick.bCanEverTick = true;

	C_rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Lers"));

	RootComponent = C_rootBox;

	state = CB_walking;
}

AEnemy2D::~AEnemy2D()
{
	///insert death sound or smthg
}

// Called when the game starts or when spawned
void AEnemy2D::BeginPlay()
{
	bGameEnd = false;
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), player);
	timer = timerValue;
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

	///Maxdistance can be adjusted in editor via blueprint

	if (player.Num() <= 0)
	{
		ADemoGameBase::Debugger(888, 0, FString("Didnt find player"));
		return;
	}

	///----ADD overlapping prevention
	FVector newLoc = GetActorLocation();
	FVector b = player.Last()->GetActorLocation();
	FVector temp = b - GetActorLocation();
	temp.Normalize();

	///Distance checker
	if (FMath::Abs(FVector::Distance(GetActorLocation(), b)) > maxDistance)
	{
		if (state != CB_walking) state = CB_walking;

		timer = timerValue;
	}
	else
	{
		if (state != CB_fighting) state = CB_fighting;

		timer -= Deltatime;
	}

	///take action based on the current state
	if (state == CB_walking)
	{
		newLoc.X += temp.X * Deltatime * moveValue;
		SetActorLocation(newLoc);
		direction = temp;
	}
	else
	{
		if (timer <= 0.0f)
		{
			bool side = direction.X > 0 ? true : false;
			asdf(side);
			direction = FVector::ZeroVector;
			ADemoGameBase::Debugger(676, (int)timer, FString("Destoyrnbkdrv"));
		}
	}

	if (direction != FVector::ZeroVector)
	{
		if (item)
			Cast<UPickupComponent>(item->GetClass())->CheckLocation(this, direction.GetSafeNormal(), item);
	}
}

///put more content relating to game ending on player death 
void AEnemy2D::PlayerDeath()
{
	bGameEnd = true;
	ADemoGameBase::Debugger(10, 0, FString("Game stopped for enemy"));
}

void AEnemy2D::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Cast<UPickupComponent>(item->GetClass())->DisEquip(item);
	UScoreManager::AddPoints(100);
	Super::EndPlay(EndPlayReason);
}

void AEnemy2D::AssignWeapon(AActor *weapon)
{
	if (!item)
	{
		item = weapon;
		Cast<UPickupComponent>(item->GetClass())->CheckLocation(this, direction.GetSafeNormal(), item);
	}

}

