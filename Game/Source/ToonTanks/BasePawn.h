
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

	void HandleDestruction();

protected:
	void RotateTurret(FVector Direction);
	void Fire();

	UPROPERTY(EditAnywhere, Category = "ProjectileType")
	TSubclassOf<class AProjectile> ProjectileClass;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseComponents", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseComponents", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseComponents", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseComponents", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathFX;

	UPROPERTY(EditAnywhere)
	class USoundBase* DeathSFX;

	void CreateProjectile();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> ExplodeCameraShakeClass;
};
