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

AEnemy2D::AEnemy2D()
{
	PrimaryActorTick.bCanEverTick = true;

	C_rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Lers"));

	RootComponent = C_rootBox;
	state = CB_walking;
	health = 1;
}

void AEnemy2D::BeginPlay()
{
	bGameEnd = false;
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), player);
	timer = timerValue;
	bIsWaiting = false;
	bIsHead = true;
	if (player.Last())
		direction = player.Last()->GetTransform().GetLocation() - GetTransform().GetLocation();
}

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

	FVector newLoc = GetTransform().GetLocation();
	FVector b = player.Last()->GetTransform().GetLocation();
	FVector temp = b - GetTransform().GetLocation();
	temp.Normalize();

	StateChecker(Deltatime, b);

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
				asdf(direction.X > 0);
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
			Cast<UPickupComponent>(item->GetClass())->CheckLocation(this, direction, item);
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

void AEnemy2D::TakeDamageEnemy(float amount)
{
	health -= amount;
	if (health < 0)
	{
		Destroy();
	}
}

void AEnemy2D::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (item)
		Cast<UPickupComponent>(item->GetClass())->DisEquip(item);
	if (item2)
		item2->Destroy();
	UScoreManager::AddPoints(100);
	Super::EndPlay(EndPlayReason);

}

//Binded to blueprint 
void AEnemy2D::Shoot()
{
	item->UseWeapon();
}

void SpawnWeapon(AItem *&item, AActor *actor, UWorld *world, UClass *weaponPrefab)
{
	indexWep = Increment(indexWep);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Name = FName(*Entityname(FString("Weapons"), indexWep));
	item = world->SpawnActor<AItem>(weaponPrefab, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
	item->Tags.Add(SpawnInfo.Name);
	item->SetActorLocation(actor->GetTransform().GetLocation());
}

//Generates weapon for the enemy based on its blueprint
void AEnemy2D::AddWeapon(int index)
{
	if (index == 1)
	{
		SpawnWeapon(item, this, GetWorld(), weaponPrefab);
		if (item)
			Cast<UPickupComponent>(item)->Pickup(this, direction, item);
	}

	if (index == 2)
	{
		SpawnWeapon(item2, this, GetWorld(), weaponPrefab);
		if (item2)
			Cast<UPickupComponent>(item2)->Pickup(this, direction, item2);
	}

}

