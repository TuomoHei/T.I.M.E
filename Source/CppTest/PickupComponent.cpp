// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupComponent.h"
#include "TestPlayerController.h"
#include "DemoGameBase.h"

// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPickupComponent::Pickup(AActor *Player, FVector location, AActor *targetObj)
{
	if (Player && targetObj)
	{
		CheckLocation(Player, location, targetObj);
	}
}

void UPickupComponent::DisEquip(AActor* targetObj)
{
	targetObj->DetachRootComponentFromParent();

	targetObj->Destroy();
}

void UPickupComponent::CheckLocation(AActor *Player, FVector location, AActor *targetObj)
{
	FAttachmentTransformRules a = FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);

	a.ScaleRule = EAttachmentRule::KeepWorld;
	a.RotationRule = EAttachmentRule::KeepWorld;

	auto comp = location.X > 0 ? 
	Player->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Right")) 
	: Player->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Left"));

	if(comp.Num() > 0)
	targetObj->AttachToComponent(Cast<USceneComponent>(comp.Last()), a);
}

