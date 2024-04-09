
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;

	TrailFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailFX"));
	TrailFX->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if (LaunchSFX) {
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSFX, GetActorLocation());
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	auto MyOwner = GetOwner();
	if (!MyOwner) 
	{
		Destroy();
		return;
	}

	if (OtherActor && OtherActor != MyOwner && OtherActor != this) 
	{
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmt, 
								  	  MyOwner->GetInstigatorController(), 
								  	  this, UDamageType::StaticClass());
		if (HitFX) {
			UGameplayStatics::SpawnEmitterAtLocation(this, HitFX, GetActorLocation(), GetActorRotation());
		}
		if (HitSFX) {
			UGameplayStatics::PlaySoundAtLocation(this, HitSFX, GetActorLocation());
		}
		if (HitCameraShakeClass) {
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	Destroy();
}
