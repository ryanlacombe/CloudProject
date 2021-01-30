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

	//Get Owner's runtime
	float GameTime = owner->GetGameTimeSinceCreation();

	//Calculate height if going up
	if (!HoveringZNegative)
	{
		float DeltaHeight = (FMath::Sin(GameTime + DeltaTime) - FMath::Sin(GameTime));
		NewLocation.Z += DeltaHeight * 200.0f;
	}
	//If going down
	else
	{
		float DeltaHeight = (FMath::Sin(GameTime + DeltaTime) - FMath::Sin(GameTime));
		NewLocation.Z -= DeltaHeight * 200.0f;
	}

	//Calculate if going Y positive
	if (!HoveringYNegative)
	{
		float DeltaDepth = (FMath::Sin(GameTime + DeltaTime) - FMath::Cos(GameTime));
		NewLocation.Y += DeltaDepth * 5.0f;
	}
	//If going Y negative
	else
	{
		float DeltaDepth = (FMath::Cos(GameTime + DeltaTime) - FMath::Sin(GameTime));
		NewLocation.Y -= DeltaDepth * 300.0f;
	}

	//Calculate if going X positive
	if (HoveringXNegative)
	{
		float DeltaLength = (FMath::Cos(GameTime + DeltaTime) - FMath::Cos(GameTime));
		NewLocation.X += DeltaLength * 20.0f;
	}
	//If going X negative
	else
	{
		float DeltaLength = (FMath::Cos(GameTime + DeltaTime) - FMath::Cos(GameTime));
		NewLocation.X -= DeltaLength * 20.0f;
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