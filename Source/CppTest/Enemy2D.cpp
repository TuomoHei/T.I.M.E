// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy2D.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "UObjectGlobals.h"
#include "EngineUtils.h"
#include "Player2D.h"
#include "Item.h"
#include "DemoGameBase.h"
#include "PickupComponent.h"
#include "ScoreManager.h"

	///rest of the implementation relating to different enemy behaviour is done via BP

static int indexWep = 0;

AEnemy2D::AEnemy2D()
{
	PrimaryActorTick.bCanEverTick = true;

	C_rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Lers"));

	RootComponent = C_rootBox;
	id = 0;
	state = CB_walking;

}


void AEnemy2D::BeginPlay()
{
	bGameEnd = false;
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), player);
	timer = timerValue;
	bIsWaiting = false;
	bIsHead = true;
	direction = player.Last()->GetActorLocation() - GetActorLocation();}

void AEnemy2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bGameEnd && !bIsWaiting)
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
		ADemoGameBase::Debugger(888, 0, FString("Didn't find player"));
		return;
	}

	FVector newLoc = GetActorLocation();
	FVector b = player.Last()->GetActorLocation();
	FVector temp = b - GetActorLocation();
	temp.Normalize();

	StateChecker(Deltatime,b);

	///take action based on the current state
	if (state == CB_walking)
	{
		newLoc.X += temp.X * Deltatime * moveValue;
		SetActorLocation(newLoc);

	}
	else
	{
		if (!item)
		{
			if (timer <= 0.0f)
			{
				bool side = direction.X > 0 ? true : false;
				asdf(side);
			}
		}
		else
		{
			if (bIsHead)
			{
				///Calls Blueprints shootevent
				ShootEvent();
			}
		}
	}

	if (direction != FVector::ZeroVector)
	{
		if (item)
		{
			Cast<UPickupComponent>(item->GetClass())->CheckLocation(this, direction.GetSafeNormal(), item);
		}
	}
}

void AEnemy2D::StateChecker(float Deltatime, FVector b)
{
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
}

///put more content relating to game ending on player death 
void AEnemy2D::PlayerDeath()
{
	bGameEnd = true;
	ADemoGameBase::Debugger(10, 0, FString("Game stopped for enemy"));
}

void AEnemy2D::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (item)
		Cast<UPickupComponent>(item->GetClass())->DisEquip(item);
	UScoreManager::AddPoints(100);
	Super::EndPlay(EndPlayReason);

}

//Binded to blueprint 
void AEnemy2D::Shoot()
{
	item->UseWeapon();
}

//Generates weapon for the enemy based on its blueprint
void AEnemy2D::AddWeapon()
{
	indexWep = Increment(indexWep);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Name = FName(*Entityname(FString("Weapons"), indexWep));
	weaponPrefab->Rename(*Entityname(FString("Weapons"),indexWep));
	item = GetWorld()->SpawnActor<AItem>(weaponPrefab, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
	item->Tags.Add(SpawnInfo.Name);
	item->SetActorLocation(GetActorLocation());
	if (item)
		Cast<UPickupComponent>(item->GetClass())->Pickup(this, direction.GetSafeNormal(), item);

}

