// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

UCLASS()
class CPPTEST_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:
	enum RechargeState
	{
		ENPTY,
		RECHARGING,
		FULL
	};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	static ATimeManager* GetInstance(UObject* WorldContextObject);
	void StartSlow();
	void StopSlow();

	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		void SetSlow(bool isEnabled) { bIsSlow = isEnabled; }
	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		bool GetSlow() { return bIsSlow; }

private:
	UPROPERTY(EditAnywhere)
		float TimeLimit;
	UPROPERTY(EditAnyWhere)
		float SlowRate;
	UPROPERTY(EditAnyWhere)
		float DefaultRate;
	UPROPERTY(EditAnywhere, Category = "TimeManager")
		bool bIsSlow;
	float CurrentTime;

	static ATimeManager* Instance;
	RechargeState State;

private:
	// Sets default values for this actor's properties
	// private constructor
	ATimeManager();
	static void FindInstance(UObject* WorldContextObject);
};
