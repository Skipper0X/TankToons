#pragma once

#include "CoreMinimal.h"
#include "PawnTank.h"
#include "Pawns/PawnBase.h"
#include "PawnTurret.generated.h"

/**
 * PawnBase Derivation Which Is Going To Contains Logic States For Turret Pawn
 */
UCLASS()
class TANKY_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta=(AllowPrivateAccess = true))
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta=(AllowPrivateAccess = true))
	float FireRange = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta=(AllowPrivateAccess = true))
	APawnTank* PlayerRef;

	FTimerHandle FireRateTimerHandle;

	auto CheckFireCondition() -> void;
	auto IsPlayerInRange() const -> bool;
	auto GetDistanceToPlayer() const -> float;

public:
	APawnTurret();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnDestroy() override;
};
