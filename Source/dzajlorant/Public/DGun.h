// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGun.generated.h"

UCLASS()
class DZAJLORANT_API ADGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* ImpactSound;
	
	UPROPERTY(EditAnywhere)
	float MaxRange = 2000;

	UPROPERTY(EditAnywhere)
	float Damage = 25;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerConstroController() const;
};
