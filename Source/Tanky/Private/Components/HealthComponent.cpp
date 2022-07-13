#include "Components/HealthComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentHp(DefaultHp);
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
}

void UHealthComponent::OnTakeDamage(AActor* DamageReceiverActor, const float Damage, const UDamageType* DamageType,
                                    AController* Controller, AActor* DamageProviderActor)
{
	if (Damage == 0) return;
	if (CurrentHp <= 0) return;

	SetCurrentHp(FMath::Clamp(CurrentHp - Damage, 0.0f, DefaultHp));

	if (CurrentHp <= 0.0f) GameModeRef->OnActorDestroy(GetOwner());
}

auto UHealthComponent::SetCurrentHp(const float Hp) -> void { CurrentHp = Hp; }
