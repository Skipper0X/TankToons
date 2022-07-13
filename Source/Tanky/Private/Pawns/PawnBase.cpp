#include "Pawns/PawnBase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	SetRootComponent(CapsuleComponent);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	BodyMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	ProjSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::Fire()
{
	if (ProjectileClass == nullptr) return;

	const FVector SpawnPos = ProjSpawnPoint->GetComponentLocation();
	const FRotator SpawnRot = ProjSpawnPoint->GetComponentRotation();

	const auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnPos, SpawnRot);
	Projectile->SetOwner(this);
}

void APawnBase::RotateTurret(const FVector LookAt)
{
	const FVector TurretInitLocation = TurretMesh->GetComponentLocation();
	const FVector LookAtX = FVector(LookAt.X, LookAt.Y, TurretMesh->GetComponentLocation().Z);
	const FRotator TurretRotation = FVector(LookAtX - TurretInitLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::OnDestroy()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DestroyVfx, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DestroySound, GetActorLocation());
	UGameplayStatics::GetPlayerController(this, 0)->ClientStartCameraShake(DestroyCameraShake);
}
