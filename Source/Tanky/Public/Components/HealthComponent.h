#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameModes/TankGameModeBase.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TANKY_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float DefaultHp = 100.0f;

	float CurrentHp = 0.0f;
	ATankGameModeBase* GameModeRef;

	auto SetCurrentHp(float Hp) -> void;
public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTakeDamage(AActor* DamageReceiverActor, float Damage, const UDamageType* DamageType, AController* Controller,
	                  AActor* DamageProviderActor);
};
