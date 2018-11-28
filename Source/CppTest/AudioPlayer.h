// Fill out your copyright notice in the Description page of Project Settings.

// Simpliest audio player possible in UE TM

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

public:	
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//// Default location to play the sound (= center of screen)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	FVector defaultLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class USoundBase*> sounds;
	
	void PlaySound(int soundIndex);
	void PlaySound(int soundIndex, FVector location);

private:
	UPROPERTY()
		UWorld *world;

	UPROPERTY()
		class USoundBase* sound;
};

