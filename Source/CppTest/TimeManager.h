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
private:
	UPROPERTY(EditAnywhere)
		float TimeLimit;
	UPROPERTY(EditAnyWhere)
		float SlowRate;
	UPROPERTY(EditAnyWhere)
		float DefaultRate;
	bool bIsSlow;
	float CurrentTime;

	static ATimeManager* Instance;
private:
	// Sets default values for this actor's properties
	// private constructor
	ATimeManager();
	static void FindInstance(UObject* WorldContextObject);
};
