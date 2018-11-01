// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TestPlayerController.generated.h"



UCLASS()
class CPPTEST_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	FVector HitPos;

	FVector2D previousTouchLocation;
	FVector2D newTouchLocation;

	class APlayer2D *RegPlayer2D;


	//virtual void GetInputTouchState(ETouchIndex::Type FingerIndex, float &LocationX, float &LocationY, bool &bIsCurrentlyPressed) override;
	virtual void SetupInputComponent() override;
	void Touched(ETouchIndex::Type, FVector Location);
	void RegisterPlayer2D(APlayer2D *actor);


	virtual void BeginPlay() override;
	
	
};
