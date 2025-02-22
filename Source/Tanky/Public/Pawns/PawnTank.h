#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Pawns/PawnBase.h"
#include "PawnTank.generated.h"

/**
 * PawnBase Derivation Which Is Going To Contains Logic States For Tank Pawn
 */
UCLASS()
class TANKY_API APawnTank : public APawnBase
{
	GENERATED_BODY()

private:
	// -> COMPONENTS.....
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;
	// -> Configs.....
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
	float RotateSpeed = 100.0f;

	FVector MoveDirection;
	FQuat RotateDirection;
	bool IsPlayerAlive = true;
	APlayerController* PlayerControllerRef = nullptr;

	void ProcessMoveInput(float Value);
	void ProcessRotationInput(float Value);

	void Move();
	void Rotate();
	void RotateTurretToCursor();

public:
	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnDestroy() override;

	auto GetIsPlayerAlive() const -> bool;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
