// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UFUNCTION(BlueprintCallable, Category = "TimeManipulate")
	void Action(float regainTime);

private:
	float Speed;
	float OldSpeed;
	ATimeManager* pTimeManager;

	FVector Position;
	FVector OldPosition;
private:
	void ChangeSlow();
	void ChangeNormal();
};
