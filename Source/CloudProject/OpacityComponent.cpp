// Fill out your copyright notice in the Description page of Project Settings.


#include "OpacityComponent.h"

// Sets default values for this component's properties
UOpacityComponent::UOpacityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpacityComponent::BeginPlay()
{
	Super::BeginPlay();

	//Calls the Opacity function
	CheckOpacity();
	
}


// Called every frame
void UOpacityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UOpacityComponent::CheckOpacity()
{
	if (OpacityLevel >= 100)
	{
		UE_LOG(LogTemp, Warning, TEXT("Whoa, you made an object more than 100% opaque!"));
	}
	else if (OpacityLevel <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Even if this worked you wouldn't be able to see the cloud!"));
	}
}
