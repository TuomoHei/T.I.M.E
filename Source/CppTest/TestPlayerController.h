// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TimeManipulator.h"
#include "TestPlayerController.generated.h"



UCLASS()
class CPPTEST_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	FVector HitPos;
	class APlayer2D *RegPlayer2D;
	class ADemoGameBase *RegGameBase;

	virtual void SetupInputComponent() override;
	void Touched(ETouchIndex::Type, FVector Location);
	void RegisterPlayer2D(APlayer2D *actor);
	void RegisterGameBase(class ADemoGameBase *base);
	void AttackEnemy(FHitResult *hit, bool Weapon);
	bool WeaponCheck(FHitResult hit);
	virtual void BeginPlay() override;
	
private:
	void GetTimeManipulator();

	UPROPERTY(EditAnywhere)
		UTimeManipulator* timeManager;
};
