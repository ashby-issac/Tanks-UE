
#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Engine/World.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector HitPoint)
{
    FVector DirectionToRotate = HitPoint - TurretMesh->GetComponentLocation();
    FRotator LookRotation = FRotator(0.f, DirectionToRotate.Rotation().Yaw, 0.f);
    FRotator NewRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(), 
                                            LookRotation, 
                                            UGameplayStatics::GetWorldDeltaSeconds(this), 
                                            5.f);
    TurretMesh->SetWorldRotation(NewRotation);
}

void ABasePawn::Fire()
{
	AProjectile* ProjectileInstance = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
										SpawnPoint->GetComponentLocation(),
										SpawnPoint->GetComponentRotation());
	ProjectileInstance->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	if (DeathFX) {
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathFX, GetActorLocation(), GetActorRotation());
	}

	if (DeathSFX) {
		UGameplayStatics::PlaySoundAtLocation(this, DeathSFX, GetActorLocation());
	}

	if (ExplodeCameraShakeClass) {
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ExplodeCameraShakeClass);
	}
}