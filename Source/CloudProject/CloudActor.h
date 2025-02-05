// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoverComponent.h"
#include "OpacityComponent.h"
#include "CloudActor.generated.h"

UCLASS()
class CLOUDPROJECT_API ACloudActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloudActor();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UHoverComponent* HoveringComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UOpacityComponent* OpacityComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
