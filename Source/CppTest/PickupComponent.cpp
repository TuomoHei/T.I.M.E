// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupComponent.h"
#include "TestPlayerController.h"
#include "DemoGameBase.h"
#include "Enemy2D.h"
#include "Item.h"

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
	if (!targetObj) return;
	FDetachmentTransformRules a(FDetachmentTransformRules::KeepWorldTransform);
	a.ScaleRule = EDetachmentRule::KeepWorld;
	targetObj->DetachFromActor(a);
}

//Check the weapons location 
//Note: removes the previous attachment
void UPickupComponent::CheckLocation(AActor *Player, FVector location, AActor *targetObj)
{
	if (!IsValid(targetObj)) return;
	FAttachmentTransformRules a = FAttachmentTransformRules(EAttachmentRule::KeepWorld, false);

	
	auto comp = Player->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Right"));

	if (comp.Num() > 0 && location.X != 0)
	{
		targetObj->AttachToComponent(Cast<USceneComponent>(comp.Last()), a);
	}

	if (Player->IsA(AEnemy2D::StaticClass()))
	{
		auto comp = location.X > 0 ?
			Player->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Right"))
			: Player->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Left"));
		if (Cast<AEnemy2D>(Player)->item2 != NULL)
		{
			auto comp = (Player->GetActorLocation() - location).X < 0 ?
				Player->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Right"))
				: Player->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Left"));
			Cast<AEnemy2D>(Player)->item2->AttachToComponent(Cast<USceneComponent>(comp.Last()), a);
		}
	}


	AItem *offset = Cast<AItem>(targetObj);
	if (IsValid(offset))
	{

		targetObj->SetActorRelativeRotation(offset->ItemOffset.GetRotation());
		targetObj->SetActorRelativeLocation(offset->ItemOffset.GetLocation());

	}
}

