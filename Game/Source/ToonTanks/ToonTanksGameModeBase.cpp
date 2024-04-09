// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    TowersCount = GetTowersCount();
    HandleGameStart();
}

void AToonTanksGameModeBase::HandleGameStart()
{
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (!ToonTanksPlayerController) return;

    StartGame();
    ToonTanksPlayerController->SetPlayerEnabledState(false);

    FTimerHandle PlayerEnabledTimerHandle;
    FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, 
                                                                 &AToonTanksPlayerController::SetPlayerEnabledState, true);
    GetWorldTimerManager().SetTimer(PlayerEnabledTimerHandle, 
                                    PlayerEnabledTimerDelegate, 
                                    StartDelay, false);
}

void AToonTanksGameModeBase::ActorDied(AActor* DestroyedActor)
{
    if (DestroyedActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController) 
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if (ATower* Tower = Cast<ATower>(DestroyedActor)) 
    {
        Tower->HandleDestruction();
        TowersCount--;
        if (TowersCount < 1)
        {
            GameOver(true);
        }
    }
}

int32 AToonTanksGameModeBase::GetTowersCount()
{
    TArray<AActor*> Actors;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Actors);
    return Actors.Num();
}
