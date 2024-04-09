
#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool IsAlive;

protected:
	virtual void BeginPlay() override;

	void FireAlarm(UInputComponent* PlayerInputComponent);


private:
	UPROPERTY(VisibleAnywhere, Category = "ViewComponents")
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "ViewComponents")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, Category = "MovementVariables")
	float MoveSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementVariables", meta = (AllowPrivateAccess = "true"))
	float TurnSpeed = 80.f;

	APlayerController* TankPlayerController;

	void Move(float Value);
	void Turn(float Value);
};
