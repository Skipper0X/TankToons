#include "GameModes/TankGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Pawns/PawnTurret.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), OutActors);

	TurretsCount = OutActors.Num();
	PlayerTankRef = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	OnStartGame();
}

auto ATankGameModeBase::OnStartGame() -> void { StartGame(); }

auto ATankGameModeBase::OnGameOver(const bool PlayerWon) -> void { GameOver(PlayerWon); }

auto ATankGameModeBase::OnActorDestroy(AActor* Actor) -> void
{
	// 0: Check If The Actor Is Player & If So Then GameOver...
	if (PlayerTankRef == Actor)
	{
		PlayerTankRef->OnDestroy();
		OnGameOver(false);
		return;
	}

	// 1: Trying Cast It To TurretPawn If So Then See If Any Turret Remaining...
	if (APawnTurret* Turret = Cast<APawnTurret>(Actor))
	{
		Turret->OnDestroy();
		if (--TurretsCount == 0) OnGameOver(true);
	}
}
