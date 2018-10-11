// Fill out your copyright notice in the Description page of Project Settings.

#include "Player2D.h"
#include "DemoGameBase.h"
#include "Components/InputComponent.h"




// Sets default values
APlayer2D::APlayer2D()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	C_PBase = CreateDefaultSubobject<UBoxComponent>(TEXT("a"));
	RootComponent = C_PBase;

	//SpringArm for camera movement
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->SetupAttachment(C_PBase);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 1.0f;



	//Camera component for player
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APlayer2D::BeginPlay()
{
	Super::BeginPlay();
	
	InputComponent = NewObject<UInputComponent>(UInputComponent::StaticClass(), 
		TEXT("InputComponent"));
	SetupPlayerInputComponent(InputComponent);
}

// Called every frame
void APlayer2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!MovementInput.IsZero())
	{
		
		//Scale our movement input axis values by 100 units per second
		MovementInput = MovementInput.GetSafeNormal() * 100.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void APlayer2D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &APlayer2D::MoveRight);
}

void APlayer2D::MoveRight(float axisValue)
{
	MovementInput.X = FMath::Clamp<float>(axisValue, -1.0f, 1.0f);
}

void APlayer2D::PlayerDeath()
{
	ADemoGameBase::Debugger(100, 0, FString("Overlapping"));
	TArray<AActor*> gamemanager;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADemoGameBase::StaticClass(), gamemanager);
	ADemoGameBase *temp = Cast<ADemoGameBase>(temp[0].GetClass());
	temp->OnPlayerDeath();
}