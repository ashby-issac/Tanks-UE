// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	void ActorDied(AActor* DestroyedActor);

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool State);

private:
	class ATank* Tank; 
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;
	int32 TowersCount = 0;
	
	void HandleGameStart();
	int32 GetTowersCount();

};
