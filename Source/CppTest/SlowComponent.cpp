// Fill out your copyright notice in the Description page of Project Settings.

#include "SlowComponent.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "Engine/Classes/Engine/Engine.h"


float USlowComponent::SpeedRate = 0.0f;

// Sets default values for this component's properties
USlowComponent::USlowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlowComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USlowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Change speed each actor
	GetOwner()->CustomTimeDilation = SpeedRate;


	GEngine->AddOnScreenDebugMessage(
		-1,
		GetWorld()->DeltaTimeSeconds,
		FColor::Yellow,
		"CurrentSpeed:" + FString::SanitizeFloat(SpeedRate)
	);
}

