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
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	OnStartGame();
}

auto ATankGameModeBase::OnStartGame() -> void
{
	// 0: Start The Game Push Widget On ViewPort & Start Countdown....
	StartGame();

	// 1: Disable Player Input Until The Spawn Delay Is Passed....
	PlayerControllerRef->SetPlayerState(false);
	FTimerHandle PlayerTimerHandle;
	const FTimerDelegate PlayerStateEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
		&APlayerControllerBase::SetPlayerState,
		true);
	GetWorld()->GetTimerManager().SetTimer(PlayerTimerHandle, PlayerStateEnableDelegate, StartDelay, false);
}

auto ATankGameModeBase::OnGameOver(const bool PlayerWon) -> void
{
	GameOver(PlayerWon);
}

auto ATankGameModeBase::OnActorDestroy(AActor* Actor) -> void
{
	// 0: Check If The Actor Is Player & If So Then GameOver...
	if (PlayerTankRef == Actor)
	{
		PlayerTankRef->OnDestroy();
		PlayerControllerRef->SetPlayerState(false);
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
