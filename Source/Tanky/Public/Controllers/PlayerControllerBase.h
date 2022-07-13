#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

UCLASS()
class TANKY_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	auto SetPlayerState(const bool Enable) -> void;
};
