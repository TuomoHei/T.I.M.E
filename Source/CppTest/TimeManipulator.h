// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/ActorComponent.h"
#include "AudioPlayer.h"
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

protected:
	FTimerHandle SlowTimeHandle;
	void ResetTimerHandle();

public:

	UPROPERTY(EditAnywhere, Category = "TimeDilation")
		float slowGameSpeed = 0.2f;

	UPROPERTY(EditAnywhere, Category = "TimeDilation")
		float defaultSpeed = 1.0f;	// NOTE: this is just for debugging

	UPROPERTY(EditAnywhere, Category = "TimeDilation")
		float slowSpeedDuration = 2.0f;
	
	UPROPERTY(EditAnywhere, Category = "TimeDilation")
		float defaultSpeedDuration = 0.2f;		

	UFUNCTION(BlueprintCallable)
		void ActivateSlowmotion();		
	
	UFUNCTION()
		void DeactivateSlowmotion();	

	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		bool GetSlow() { return bIsSlow; }

	UFUNCTION(BlueprintCallable)
		void DeactivateSlowmotionPermanent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AAudioPlayer *audioPlayer;

	UPROPERTY(EditAnywhere)
		float slowAudioPitch = 0.2f;

	UPROPERTY(EditAnywhere)
		float audioPitchInterp = 0.075f;

	//UPROPERTY(EditAnyWhere)
	//	class USoundBase* sound;

	UPROPERTY(BlueprintReadOnly)
	bool bIsSlow;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	float testFloat = 13;
};
