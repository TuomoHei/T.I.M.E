// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TimeManager.h"
#include "TimeManipulator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPTEST_API UTimeManipulator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeManipulator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//	UFUNCTION(BlueprintCallable, Category = "TimeManipulate")
//	void Action();
//
//private:
//
//	UPROPERTY(EditAnyWhere)
//		float BackSlowWait;
//	float Speed;
//	float OldSpeed;
//	ATimeManager* pTimeManager;
//
//	FVector Position;
//	FVector OldPosition;
//	FTimerHandle TimeHandle;
//	
//private:
//	void ChangeNormal();
//	void ChangeSlow();
//	void CangeForcedSlow();

protected:
	FTimerHandle SlowTimeHandle;
	void ResetTimerHandle();

	UFUNCTION()
		void DeactivateSlowmotionPermanent();
	
public:

	UPROPERTY(EditAnywhere, Category = "TimeDilation")
		float slowGameSpeed = 0.2f;

	UPROPERTY(EditAnywhere, Category = "TimeDilation")
		float defaultSpeed = 1.0f;	// NOTE: this is just for debugging

	UPROPERTY(EditAnywhere, Category = "TimeDilation")
		float slowSpeedDuration = 2.0f;
	
	UPROPERTY(EditAnywhere, Category = "TimeDilation")
		float defaultSpeedDuration = 0.2f;		

	UFUNCTION()
		void ActivateSlowmotion();		
	
	UFUNCTION()
		void DeactivateSlowmotion();	

	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		bool GetSlow() { return bIsSlow; }

private:
	bool bIsSlow;

};
