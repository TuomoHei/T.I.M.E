// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Enemy2D.h"
#include "DemoGameBase.h"
#include "Runtime/Engine/Public/TimerManager.h"

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

void AItem::DestroyFunc()
{
	if (this) return;

	if (this->GetAttachParentActor()) return;
	FTimerHandle a;
	FTimerDelegate weaponDel;
	weaponDel.BindUFunction(this, FName("DestroyWeapon"));
	GetWorld()->GetTimerManager().SetTimer(a, weaponDel, destroyTime, false);
}

void AItem::DestroyWeapon()
{
	if (!this->GetAttachParentActor())
	{
		GeneralDestroyer(this, GetWorld());
	}
}







