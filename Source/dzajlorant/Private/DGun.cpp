#include "dzajlorant/Public/DGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

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
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location,  End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	
	if (bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location,ShotDirection.Rotation() );
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
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

