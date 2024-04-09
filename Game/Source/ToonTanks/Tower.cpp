
#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATower::ATower()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle,
                                    this,
                                    &ATower::CheckFireCondition, 
                                    FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::CheckFireCondition()
{
    if (InFireRange() && Tank->IsAlive)
    {
        Fire();
    }
}

bool ATower::InFireRange() const
{
    return Tank && FVector::Dist(Tank->GetActorLocation(), GetActorLocation()) < FireRange;
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}
