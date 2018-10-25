// Fill out your copyright notice in the Description page of Project Settings.

#include "Player2D.h"
#include "TestPlayerController.h"
#include "DemoGameBase.h"
#include "Components/InputComponent.h"

APlayer2D::APlayer2D()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	C_PBase = CreateDefaultSubobject<UBoxComponent>(TEXT("a"));
	RootComponent = C_PBase;
}

// Called when the game starts or when spawned
void APlayer2D::BeginPlay()
{
	Super::BeginPlay();

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

void APlayer2D::PlayerDeath()
{
	TArray<AActor*> gamemanager;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADemoGameBase::StaticClass(), gamemanager);
	ADemoGameBase *temp = Cast<ADemoGameBase>(temp[0].GetClass());
	temp->OnPlayerDeath();
}
