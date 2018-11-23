// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy2D.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "UObjectGlobals.h"
#include "EngineUtils.h"
#include "Player2D.h"
#include "TestPlayerController.h"
#include "Item.h"
#include "DemoGameBase.h"
#include "PickupComponent.h"
#include "ScoreManager.h"

	///rest of the implementation relating to different enemy behaviour is done via BP
static auto GeneralDestroyer = [](AActor *entity, UWorld *world) {if (!entity) return; 
if (!entity->IsValidLowLevel())return; 
entity->K2_DestroyActor();
entity = NULL;
world->ForceGarbageCollection(true); 
ADemoGameBase::Debugger(443, 0, FString("KILLEd")); 
};



AEnemy2D::AEnemy2D()
{
	PrimaryActorTick.bCanEverTick = true;

	C_rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Lers"));

	RootComponent = C_rootBox;
	state = CB_walking;
}

void AEnemy2D::BeginPlay()
{
	bGameEnd = false;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), player);
	timer = timerValue;
	bIsWaiting = false;
	bIsHead = true;
	Super::BeginPlay();

}

void AEnemy2D::Tick(float DeltaTime)
{
	if (!this) return;
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

	if (player.Last())
		direction = player.Last()->GetTransform().GetLocation() - GetTransform().GetLocation();

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

		if (item2)
		{
			Cast<UPickupComponent>(item2->GetClass())->CheckLocation(this, direction, item2);
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


void AEnemy2D::TakeDamageEnemy(bool weapon)
{
	//check if player is holding weapon
	if (weapon)
	{
		if (item2 != nullptr)
		{
			GeneralDestroyer(item2, GetWorld());
			item2 = nullptr;
		}
		ADemoGameBase::Debugger(122, 0, FString("Melee weapon hit"));

		Cast<APlayer2D>(player.Last())->PC->RegGameBase->EnemyListRemover(this);
		GeneralDestroyer(this,GetWorld());
		return;
	}
	//check if dual wielding enemy
	if (item2)
	{
		GeneralDestroyer(item2,GetWorld());
		item2 = nullptr;

	}
	//drop the last item that enemy is holding
	if (item)
	{

		Cast<UPickupComponent>(item)->DisEquip(item);
		item = nullptr;
		return;
	}

	ADemoGameBase::Debugger(122, 0, FString("destroy"));
	Cast<APlayer2D>(player.Last())->PC->RegGameBase->EnemyListRemover(this);
	//Add death animation and others here
	GeneralDestroyer(this,GetWorld());
}

void AEnemy2D::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

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
	if (index == 0)
	{
		SpawnWeapon(item, this, GetWorld(), weaponPrefab);
		if (item)
			Cast<UPickupComponent>(item)->Pickup(this, direction, item);
	}

	if (index == 1)
	{
		SpawnWeapon(item2, this, GetWorld(), weaponPrefab);
		if (item2)
			Cast<UPickupComponent>(item2)->Pickup(this, direction, item2);
	}

}

