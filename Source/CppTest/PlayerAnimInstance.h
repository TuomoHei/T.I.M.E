// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Player2D.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class CPPTEST_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:

	virtual void NativeInitializeAnimation() override;

	//APawn * Player;

	UPROPERTY(EditAnywhere)
		class APlayer2D * PlayerClass;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 attackAnimID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsSliding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsAlive;
	
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
		void UpdateAnimationProperties(); // Updates the above properties

public:

	UFUNCTION(BlueprintCallable)
		void SetAttackAnimID();
		
};
