// Fill out your copyright notice in the Description page of Project Settings.

#include "Player2D.h"
#include "TestPlayerController.h"
#include "DemoGameBase.h"
#include "Components/InputComponent.h"
#include "PickupComponent.h"

APlayer2D::APlayer2D()
{

	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	base = CreateDefaultSubobject<UBoxComponent>(TEXT("ASDF"));
	RootComponent = base;

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
}

// Called every frame
void APlayer2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MovementInput = FVector::ZeroVector;

	if (!PC)
	{
		ADemoGameBase::Debugger(20, 0, FString("Player Controller undefined"));
		return;
	}

	///Calculate the distance between click point and players location
	if (PC->HitPos != FVector::ZeroVector)
	{
		ADemoGameBase::Debugger(255, (int)(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - PC->HitPos).X, FString("Distance : "));

		if (FMath::Abs((GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - PC->HitPos).X) > 10)
		{
			MovementInput = PC->HitPos - GetActorLocation();
			MovementInput.Y = 0;
			MovementInput.Z = 0;
		}
		else
		{
			MovementInput = FVector::ZeroVector;
		}

		AddActorWorldOffset(MovementInput * DeltaTime);
	}


}

// Called to bind functionality to input
void APlayer2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayer2D::MoveRight(float axisValue)
{
	MovementInput.X = FMath::Clamp<float>(axisValue, -1.0f, 1.0f);
}

//Calls the gamemodebase method onplayerdeath 
void APlayer2D::PlayerDeath()
{
	TArray<AActor*> gamemanager;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADemoGameBase::StaticClass(), gamemanager);
	ADemoGameBase *temp = Cast<ADemoGameBase>(temp[0].GetClass());
	temp->OnPlayerDeath();
}

void APlayer2D::PlayerPickUp(AActor *targetObj)
{
	if (targetObj)
	{
		UPickupComponent *temp = Cast<UPickupComponent>(targetObj->GetClass());
		temp->Pickup(targetObj);
	}
}

void APlayer2D::DisEquip(AActor *targetObj)
{
	if (targetObj)
	{
		UPickupComponent *temp = Cast<UPickupComponent>(targetObj->GetClass());
		temp->DisEquip(targetObj);

	}
}
