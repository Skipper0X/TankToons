// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/PawnBase.h"

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

void APawnBase::Fire() const
{
	UE_LOG(LogTemp, Warning, TEXT("PawnBase :: Fire();"))
}

void APawnBase::RotateTurret(const FVector LookAt) const
{
	const FVector TurretInitLocation = TurretMesh->GetComponentLocation();
	const FVector LookAtX = FVector(LookAt.X, LookAt.Y, TurretMesh->GetComponentLocation().Z);
	const FRotator TurretRotation = FVector(LookAtX - TurretInitLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::OnDestroy()
{
}
