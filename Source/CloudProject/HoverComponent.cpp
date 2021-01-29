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
	float RunningTime = owner->GetGameTimeSinceCreation();

	//Calculate height if going up
	if (!Floatingdown)
	{
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
		NewLocation.Z += DeltaHeight * 200.0f;
	}
	//If going down
	else
	{
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
		NewLocation.Z -= DeltaHeight * 20.0f;
	}

	owner->SetActorLocation(NewLocation);
}

void UHoverComponent::SetFloatingDirection(bool floatingup)
{
	Floatingdown = !floatingup;
}

