#include "GameModes/TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

auto ATankGameModeBase::OnStartGame() -> void
{
}

auto ATankGameModeBase::OnGameOver(bool PlayerWon) -> void
{
}

auto ATankGameModeBase::OnActorDestroy(AActor* Actor) -> void
{
	UE_LOG(LogTemp, Warning, TEXT("A Pawn Died"));
}
