// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverComponent.h"

// Sets default values for this component's properties
UHoverComponent::UHoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHoverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get the Actor
	AActor* owner = GetOwner();

	//Get current location
	FVector NewLocation = owner->GetActorLocation();

	//Get StartingLocation
	FVector StartLocation = owner->GetActorLocation();

	//Get Owner's runtime
	float GameTime = owner->GetGameTimeSinceCreation();

	//Calculate height if going up
	if (!HoveringZNegative)
	{
		NewLocation.Z += ZMultiplier;
		if (NewLocation.Z >= ZMax)
		{
			HoveringZNegative = true;
		}
	}
	//If going down
	else
	{
		NewLocation.Z -= ZMultiplier;
		if (NewLocation.Z <= ZMin)
		{
			HoveringZNegative = false;
		}
	}

	//Calculate if going Y positive
	if (!HoveringYNegative)
	{
		NewLocation.Y += YMultiplier;
		if (NewLocation.Y >= YMax)
		{
			HoveringYNegative = true;
		}
	}
	//If going Y negative
	else
	{
		NewLocation.Y -= YMultiplier;
		if (NewLocation.Y <= YMin)
		{
			HoveringYNegative = false;
		}
	}

	//Calculate if going X positive
	if (!HoveringXNegative)
	{
		NewLocation.X += XMultiplier;
		if (NewLocation.X >= XMax)
		{
			HoveringXNegative = true;
		}
	}
	//If going X negative
	else
	{
		NewLocation.X -= XMultiplier;
		if (NewLocation.X <= XMin)
		{
			HoveringXNegative = false;
		}
	}

	owner->SetActorLocation(NewLocation);
}

void UHoverComponent::SetHoveringZDirection(bool HoveringZPositive)
{
	HoveringZNegative = !HoveringZPositive;
}

void UHoverComponent::SetHoveringYDirection(bool HoveringYPositive)
{
	HoveringYNegative = !HoveringYPositive;
}

void UHoverComponent::SetHoveringXDirection(bool HoveringXPositive)
{
	HoveringXNegative = !HoveringXPositive;
}