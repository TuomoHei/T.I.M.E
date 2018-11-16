// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Item.generated.h"

UCLASS()
class CPPTEST_API AItem : public APawn
{
	GENERATED_BODY()

public:

	AItem();
	UFUNCTION(BlueprintCallable)
	void Physics(float deltatime);
	UFUNCTION(BlueprintCallable)
		void Bounce(float deltatime);

	///Calls blueprint function attack
	UFUNCTION(BlueprintImplementableEvent)
		void UseWeapon();
	UPROPERTY(EditAnywhere, Category="Variables")
		FTransform ItemOffset;

protected:

	UPROPERTY(BlueprintReadWrite)
		float shoottime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ranged")
		float firerate;
	UPROPERTY(EditAnywhere, Category = "CustomPhysics")
		float weight;
	UPROPERTY(EditAnywhere, Category = "CustomPhysics")
		float groundLevel;

	// Default transform offset position when picked up

	FTransform GetOffset() { return ItemOffset; }
};
