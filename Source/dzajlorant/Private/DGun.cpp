// Fill out your copyright notice in the Description page of Project Settings.


#include "dzajlorant/Public/DGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "DShooter.h"
// Sets default values
ADGun::ADGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);
}

void ADGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, "MuzzleFlashSocket");

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	AController* OwnerController =  OwnerPawn->GetController();

	if (OwnerController == nullptr) return;

	FVector Location = OwnerPawn->GetActorLocation();
	FRotator Rotation = OwnerPawn->GetActorRotation();
	
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Rotation.Vector() * MaxRange + Location;

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location,  End, ECollisionChannel::ECC_GameTraceChannel1);
	
	
	if (bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location,ShotDirection.Rotation() );
	}
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

