// Fill out your copyright notice in the Description page of Project Settings.


#include "DShooter.h"


// Sets default values
ADShooter::ADShooter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADShooter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

