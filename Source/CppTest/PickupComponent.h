// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "PickupComponent.generated.h"


UCLASS( )
class CPPTEST_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* m_owner;
	UPROPERTY(EditAnywhere, Category = "PickUp")
		float HeightOffset;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "PickUp")
		void SetPlayer(AActor* owner) { m_owner = owner; }
	UFUNCTION(BlueprintCallable, Category = "PickUp")
		void Pickup(AActor* Player, FVector location, AActor *target);
	UFUNCTION(BlueprintCallable, Category = "PickUp")
		void DisEquip(AActor* targetObj);

	void CheckLocation(AActor *Player, FVector loc,AActor *target);

	
};
