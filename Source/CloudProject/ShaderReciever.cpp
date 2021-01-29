// Fill out your copyright notice in the Description page of Project Settings.


#include "ShaderReciever.h"

// Sets default values
AShaderReciever::AShaderReciever()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShaderReciever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShaderReciever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShaderReciever::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

