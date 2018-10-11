// Fill out your copyright notice in the Description page of Project Settings.

#include "DropItemComponent.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"



// Sets default values for this component's properties
UDropItemComponent::UDropItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// Entry Item blueprints 
	static ConstructorHelpers::FObjectFinder<UClass> FoundItemBP(TEXT("/Game/Blueprints/Weapon_BP.Weapon_BP_C"));
	ItemBP = FoundItemBP.Object;
}


// Called when the game starts
void UDropItemComponent::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Params;
	Params.bNoFail = false;
}


// Called every frame
void UDropItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Generate drop item at destroyd enmey position (called from Enemy2D_BP)
void UDropItemComponent::Drop()
{
	FVector DropPoint;
	DropPoint = this->GetOwner()->GetActorLocation();

	UWorld* World = GetWorld();
	World->SpawnActor<AActor>(ItemBP, DropPoint, FRotator::ZeroRotator);
}
