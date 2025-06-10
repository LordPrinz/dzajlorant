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
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, "MuzzleFlashSocket");
	
	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	
	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location,ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location,ShotDirection.Rotation() );
		
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerConstroController();
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

bool ADGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerConstroController();

	if (OwnerController == nullptr) return false;

	FVector Location;
	FRotator Rotation;
	
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	
	FVector End = Rotation.Vector() * MaxRange + Location;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, Location,  End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}


AController* ADGun::GetOwnerConstroController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}
