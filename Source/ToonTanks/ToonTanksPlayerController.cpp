
#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerControlsState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnabled;
}