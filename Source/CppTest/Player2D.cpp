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



APlayer2D::APlayer2D()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	base = CreateDefaultSubobject<UBoxComponent>(TEXT("ASDF"));
	RootComponent = Cast<USceneComponent>(base);
	item = nullptr;
	canMove = true;
	///Tag if needed
	Tags.Add("Player");
}

// Called when the game starts or when spawned
void APlayer2D::BeginPlay()
{
	Super::BeginPlay();

	///Find the players custom controller (testplayercontroller) and check if that exists
	PC = Cast<ATestPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC)
	{
		PC->RegisterPlayer2D(this);

		PC->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}

	GetTimeManipulator();

	// Get audio player cpp parent class
	audioPlayer = audioPlayerBP->GetDefaultObject<AAudioPlayer>();
	timeManager->audioPlayer = audioPlayer; // Tell our component time manipulator how to find audioplayer
	timeManager->ActivateSlowmotion();
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
		MovementInput = PC->HitPos - GetTransform().GetLocation().X;
		MovementInput.Normalize();
	}


	///Calculate the distance between click point and players location

	newLoc.X += Movevalue(MovementInput) * DeltaTime * moveSpeed;
	SetActorLocation(newLoc);



	if (MovementInput != FVector::ZeroVector)
	{
		//timeManager->DeactivateSlowmotion();
		if (item)
			Cast<UPickupComponent>(item->GetClass())->CheckLocation(this, MovementInput, item);
	}
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
	audioPlayer->PlaySound(8, GetWorld());
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
		Cast<UPickupComponent>(item->GetClass())->DisEquip(item);
}


void APlayer2D::AttackEnemy(AActor *enemy)
{
	if (!enemy) return;

	if (item)
	{

		Cast<AEnemy2D>(enemy)->TakeDamageEnemy(item != nullptr);
		Cast<AItem>(item)->UseWeapon();
		int32 swordSoundID = (rand() % 2) > 0 ? 3 : 4;
		audioPlayer->PlaySound(swordSoundID, GetWorld());
		bIsAttacking = false;
		return;

	}
	else
	{
		Cast<AEnemy2D>(enemy)->TakeDamageEnemy(item != nullptr);
		int32 punchSoundID = (rand() % 2) > 0 ? 1 : 2;
		audioPlayer->PlaySound(punchSoundID, GetWorld());
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

