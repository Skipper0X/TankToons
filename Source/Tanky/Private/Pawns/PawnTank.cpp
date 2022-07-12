#include "Pawns/PawnTank.h"


APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}


// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void APawnTank::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();
	RotateTurretToCursor();
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const FName FireBinding = "Fire";
	const FName TurnBinding = "Turn";
	const FName MoveForwardBinding = "MoveForward";

	PlayerInputComponent->BindAxis(TurnBinding, this, &APawnTank::ProcessRotationInput);
	PlayerInputComponent->BindAxis(MoveForwardBinding, this, &APawnTank::ProcessMoveInput);
	PlayerInputComponent->BindAction(FireBinding, IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::ProcessMoveInput(const float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::ProcessRotationInput(const float Value)
{
	const float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	const FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotateDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotateDirection, true);
}

void APawnTank::RotateTurretToCursor()
{
	if (PlayerControllerRef == nullptr) return;

	FHitResult TraceHit;
	PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHit);
	RotateTurret(TraceHit.ImpactPoint);
}

void APawnTank::OnDestroy()
{
	Super::OnDestroy();
}
