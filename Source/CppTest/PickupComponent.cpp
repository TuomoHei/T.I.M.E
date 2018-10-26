// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupComponent.h"


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

void UPickupComponent::Pickup(AActor* targetObj)
{
	EAttachmentRule *erule = new EAttachmentRule();

	FAttachmentTransformRules* rules = new FAttachmentTransformRules(*erule,true);
	rules->ScaleRule =EAttachmentRule::KeepWorld;
	rules->LocationRule = EAttachmentRule::KeepWorld;

	targetObj->AttachToActor(m_owner, *rules);

	FVector ParentPos = m_owner->GetActorTransform().GetLocation();
	targetObj->SetActorLocation(ParentPos + Offset);
}

void UPickupComponent::DisEquip(AActor* targetObj)
{
	targetObj->DetachRootComponentFromParent();

	targetObj->Destroy();
}

