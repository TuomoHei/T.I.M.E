// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioPlayer.generated.h"

UCLASS()
class CPPTEST_API AAudioPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle DelayTimeHandle;
	void ResetTimerHandle(UWorld * world);

public:	
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class USoundBase*> sounds;
	
	void PlaySound(int soundIndex, UWorld * w);
	void PlaySound(int soundIndex, float delay, UWorld * w);
	void PlaySound(int soundIndex, FVector location, UWorld * w);

private:

	FVector defaultLocation;

	UPROPERTY()
		class USoundBase* sound;
};

