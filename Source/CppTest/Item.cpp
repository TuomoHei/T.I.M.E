// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "DemoGameBase.h"

///most of the implementation and behaviour is set in blueprints

AItem::AItem()
{
	Tags.Add("PickUp");
}

void AItem::Physics(float deltatime)
{
	if (GetActorLocation().Z >= groundLevel)
	{
		FVector location = GetActorLocation();
		location.Z -= 9.81 * deltatime * weight;
		SetActorLocation(location);
	}
}

void AItem::Bounce(float deltatime)
{
	FVector location = GetActorLocation();
	location.Z += 9.81 * deltatime;
}





