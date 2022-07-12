#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

UCLASS()
class TANKY_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	USceneComponent* ProjSpawnPoint;

public:
	// Sets default values for this pawn's properties
	APawnBase();

protected:
	void Fire() const;
	void RotateTurret(const FVector LookAt) const;
	virtual void OnDestroy();
};
