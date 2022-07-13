#include "Controllers/PlayerControllerBase.h"

auto APlayerControllerBase::SetPlayerState(const bool Enable) -> void
{
	if (Enable)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = Enable;
}
