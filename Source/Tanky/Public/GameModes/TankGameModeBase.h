#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TANKY_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	auto OnStartGame() -> void;
	auto OnGameOver(bool PlayerWon) -> void;

public:
	auto OnActorDestroy(AActor* Actor) -> void;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
};
