#include "Pawns/PawnTurret.h"

#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret()
{
}

void APawnTurret::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

auto APawnTurret::CheckFireCondition() const -> void
{
	// 0: If Player Is Not Valid Or Alive , Just BAIL!!
	if (PlayerRef == nullptr) return;

	// 1: If Player Is In Range Then FIRE!
	if (IsPlayerInRange())
	{
	}
}

auto APawnTurret::IsPlayerInRange() const -> bool { return GetDistanceToPlayer() <= FireRange; }

auto APawnTurret::GetDistanceToPlayer() const -> float
{
	if (PlayerRef == nullptr) return 0.0f;
	return FVector::Dist(PlayerRef->GetActorLocation(), GetActorLocation());
}
