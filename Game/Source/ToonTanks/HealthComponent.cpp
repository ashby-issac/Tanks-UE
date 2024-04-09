
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameModeBase.h"

UHealthComponent::UHealthComponent()
{
	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ToonTanksGameMode = Cast<AToonTanksGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float DamageAmt, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (DamageAmt <= 0) return;

	Health -= DamageAmt;
	if (Health < 1 && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
}