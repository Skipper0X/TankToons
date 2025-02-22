#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ProjectileBase.generated.h"

UCLASS()
class TANKY_API AProjectileBase : public AActor
{
	GENERATED_BODY()
private:
	// -> COMPONENTS...
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = true))
	UParticleSystemComponent* ProjectileTrailVfx;

	// -> CONFIGS & REFs...
	UPROPERTY(EditDefaultsOnly, Category= "Damage")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Movement", meta=(AllowPrivateAccess = true))
	float MoveSpeed = 1300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Damage", meta=(AllowPrivateAccess = true))
	float Damage = 50.0f;
	UPROPERTY(EditAnywhere, Category= "Effects")
	UParticleSystem* HitVfx;
	UPROPERTY(EditAnywhere, Category= "Effects")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category= "Effects")
	USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category= "Effects")
	TSubclassOf<UCameraShakeBase> HitCameraShake;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	           FVector NormalImpulse, const FHitResult& HitResult);

public:
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
