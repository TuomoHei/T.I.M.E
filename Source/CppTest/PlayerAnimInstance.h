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

	APawn * Player;

	virtual void NativeInitializeAnimation() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 attackAnimID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsSliding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsAlive;
	
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
		void UpdateAnimationProperties(); // Updates the above properties

public:

	UPROPERTY (EditAnywhere)
		class APlayer2D * PlayerClass;

	UFUNCTION(BlueprintCallable)
		void SetAttackAnimID();
		
};
