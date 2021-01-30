// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLOUDPROJECT_API UHoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoverComponent();

	UPROPERTY(Category = "Hover", EditAnywhere, BlueprintReadWrite)
	bool HoveringZNegative = false;

	UPROPERTY(Category = "Hover", EditAnywhere, BlueprintReadWrite)
	bool HoveringYNegative = false;

	UPROPERTY(Category = "Hover", EditAnywhere, BlueprintReadWrite)
	bool HoveringXNegative = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetHoveringZDirection(bool HoveringZPositive);

	UFUNCTION(BlueprintCallable)
	void SetHoveringYDirection(bool HoveringYPositive);

	UFUNCTION(BlueprintCallable)
	void SetHoveringXDirection(bool HoveringXPositive);
};
