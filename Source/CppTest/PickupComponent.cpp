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
	EAttachmentRule *erule = new EAttachmentRule();
	FAttachmentTransformRules* rules = new FAttachmentTransformRules(*erule, true);
	rules->ScaleRule = EAttachmentRule::KeepWorld;
	rules->LocationRule = EAttachmentRule::KeepWorld;
	rules->RotationRule = EAttachmentRule::KeepWorld;

	if (Player && targetObj)
	{
		ADemoGameBase::Debugger(560, 0, FString("Detected item, proceeding pickup"));
		targetObj->AttachToActor(Player, *rules);
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
	FVector ParentPos = Player->GetActorTransform().GetLocation();
	targetObj->SetActorLocation(ParentPos + FVector(0.0f, 0.5f, 0.0f) + location * 20.0f);
}

