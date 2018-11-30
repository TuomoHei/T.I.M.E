// Fill out your copyright notice in the Description page of Project Settings.

#include "Player2D.h"
#include "TestPlayerController.h"
#include "PickUpComponent.h"
#include "DemoGameBase.h"
#include "Enemy2D.h"
#include "Item.h"
#include "Components/InputComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

static auto BulletDirectionL = [](FVector vector, FVector &retVector)
{
	if (vector.X > 0.1f)
		retVector = FVector(1.0f, 0.0f, 0.0f);
	else if (vector.X < -0.1f)
		retVector = FVector(-1.0f, 0.0f, 0.0f);
};

APlayer2D::APlayer2D()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Tags.Add("Player");
}

// Called when the game starts or when spawned
void APlayer2D::BeginPlay()
{
	Super::BeginPlay();
	item = nullptr;
	canMove = true;
	BulletDirection,MovementInput = FVector::ZeroVector;
	
	///Find the players custom controller (testplayercontroller) and check if that exists
	PC = Cast<ATestPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC)
	{
		PC->RegisterPlayer2D(this);

		PC->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}

	GetTimeManipulator();
}

// Called every frame
void APlayer2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	///	if (!canMove) return; uncomment when enabling player death

	if (!PC)
	{
		ADemoGameBase::Debugger(20, 0, FString("Player Controller undefined"));
		return;
	}

	if (PC->HitPos == FVector::ZeroVector) return;

	FVector newLoc = GetTransform().GetLocation();

	if (FMath::Abs(PC->HitPos.X - GetTransform().GetLocation().X) < 20)
	{
		MovementInput = FVector::ZeroVector;
	}
	else
	{
		MovementInput = PC->HitPos - GetTransform().GetLocation();
	}
	BulletDirectionL(MovementInput, BulletDirection);



	//timeManager->DeactivateSlowmotion();
	if (IsValid(item))
	{
		Cast<UPickupComponent>(item->GetClass())->CheckLocation(this, BulletDirection, item);
		if (!Cast<AItem>(item)->meleeweapon)
			return;
	}

	newLoc.X += Movevalue(MovementInput.GetSafeNormal()) * DeltaTime * moveSpeed;
	SetActorLocation(newLoc);

}

// Called to bind functionality to input
void APlayer2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


//Calls the gamemodebase method onplayerdeath 
void APlayer2D::PlayerDeath()
{
	//DEBUG NEED TO REMOVE WHEN NOT NEEDED
	return;
	TArray<AActor*> gamemanager;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADemoGameBase::StaticClass(), gamemanager);
	ADemoGameBase *temp = nullptr;
	temp = Cast<ADemoGameBase>(gamemanager[0]);
	temp->OnPlayerDeath();
	canMove = false;
}

void APlayer2D::PickUp(AActor *targetObj)
{
	if (!item)
	{
		item = targetObj;
		Cast<UPickupComponent>(targetObj->GetClass())->Pickup(this, MovementInput, item);
	}
}

void APlayer2D::UnEquip()
{
	if (item)
	{
		Cast<UPickupComponent>(item->GetClass())->DisEquip(item);
		item = nullptr;
	}
}


void APlayer2D::AttackEnemy(AActor *enemy)
{
	if (!enemy) return;

	if (item)
	{
		if (Cast<AItem>(item)->meleeweapon)
		{
			Cast<AEnemy2D>(enemy)->TakeDamageEnemy(item != nullptr);
			Cast<AItem>(item)->UseWeapon(true);
		}

		bIsAttacking = false;
		return;

	}
	else
	{
		Cast<AEnemy2D>(enemy)->TakeDamageEnemy(item != nullptr);
		bIsAttacking = false;
	}

}

void APlayer2D::GetTimeManipulator()
{
	timeManager = FindComponentByClass<UTimeManipulator>();
	if (timeManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time Manipulator found"));
	}
}

