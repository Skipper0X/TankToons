#pragma once

#include "CoreMinimal.h"
#include "Actors/ProjectileBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

UCLASS()
class TANKY_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	// -> COMPONENTS...
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	USceneComponent* ProjSpawnPoint;

	// -> VARIABLES & REFERENCES...
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Projectile Type", meta=(AllowPrivateAccess = true))
	TSubclassOf<AProjectileBase> ProjectileClass;

public:
	// Sets default values for this pawn's properties
	APawnBase();
	virtual void OnDestroy();

protected:
	virtual void Fire();
	virtual void RotateTurret(const FVector LookAt);
};
