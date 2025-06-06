// Fill out your copyright notice in the Description page of Project Settings.


#include "dzajlorant/Public/DGun.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ADGun::ADGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SkeletalMesh->SetupAttachment(Root);
}

void ADGun::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("You ve ben shot"));
}

// Called when the game starts or when spawned
void ADGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

