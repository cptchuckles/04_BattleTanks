// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;


UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	void AimAt(FVector HitLocation);

protected:
	
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION( BlueprintCallable, Category = Setup )
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION( BlueprintCallable, Category = Setup )
	void SetTurretReference(UTankTurret* TurretToSet);
	
	UFUNCTION( BlueprintCallable, Category = Tankiness )
	void Fire();
	
	UPROPERTY( EditAnywhere, Category = Firing )
	float LaunchSpeed = 8000.0f; // 80m/s
	UPROPERTY( EditAnywhere, Category = Firing )
	TSubclassOf<AProjectile> ProjectileBP = nullptr;
	
	UTankBarrel* Barrel = nullptr; //local barrel handle

};
