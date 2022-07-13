#include "Actors/ProjectileBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	SetRootComponent(ProjectileMesh);

	ProjectileTrailVfx = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Vfx"));
	ProjectileTrailVfx->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MoveSpeed;
	ProjectileMovement->MaxSpeed = MoveSpeed;

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                            FVector NormalImpulse, const FHitResult& HitResult)
{
	const AActor* CurrentOwner = GetOwner();
	if (CurrentOwner == nullptr) return;

	if (OtherActor && OtherActor != this && OtherActor != CurrentOwner)
	{
		AController* Controller = CurrentOwner->GetInstigatorController();
		UGameplayStatics::ApplyDamage(OtherActor, Damage, Controller, this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitVfx, GetActorLocation());
		Destroy();
	}
}
