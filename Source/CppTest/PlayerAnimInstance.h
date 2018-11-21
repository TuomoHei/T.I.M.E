// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class CPPTEST_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:

	virtual void NativeInitializeAnimation() override;

	//APawn * Player;

	UPROPERTY()
		class APlayer2D* PlayerClass;

	UPROPERTY()
		USkeletalMeshComponent* skeletalMeshComp;

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
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	UAnimSequenceBase* attack1;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	UAnimSequenceBase* attack2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UAnimSequenceBase*> attackAnims;

public:

	UFUNCTION(BlueprintCallable)
		void SetAttackAnimID();	

	UFUNCTION()
		float GetAttackDuration();

};
