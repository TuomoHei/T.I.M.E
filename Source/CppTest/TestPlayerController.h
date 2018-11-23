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
	class APlayer2D *RegPlayer2D;
	class ADemoGameBase *RegGameBase;

	//virtual void GetInputTouchState(ETouchIndex::Type FingerIndex, float &LocationX, float &LocationY, bool &bIsCurrentlyPressed) override;
	virtual void SetupInputComponent() override;
	void Touched(ETouchIndex::Type, FVector Location);
	void RegisterPlayer2D(APlayer2D *actor);
	void RegisterGameBase(class ADemoGameBase *base);


	virtual void BeginPlay() override;
	
	
};
