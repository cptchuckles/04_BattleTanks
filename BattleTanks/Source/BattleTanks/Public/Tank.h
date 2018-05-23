// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
//class UTankMovementComponent;
class AProjectile;


UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	void AimAt(FVector HitLocation);

	UFUNCTION( BlueprintCallable, Category = Tankiness )
	void Fire();
	
protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
	
	//UPROPERTY(BlueprintReadOnly)
	//UTankMovementComponent* TankMovementComponent = nullptr;
	
private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION( BlueprintCallable, Category = Setup )
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION( BlueprintCallable, Category = Setup )
	void SetTurretReference(UTankTurret* TurretToSet);	
	
	UPROPERTY( EditDefaultsOnly, Category = Firing )
	float LaunchSpeed = 8000.0f; // 80m/s
	UPROPERTY( EditDefaultsOnly, Category = Firing )
	TSubclassOf<AProjectile> ProjectileBP = nullptr;
	UPROPERTY( EditDefaultsOnly, Category = Firing )
	float ShellLoadDelay = 3.0; //3 second load time
	float LastFireTime = 0.0;	//annoying timestamp variable
	
	UTankBarrel* Barrel = nullptr; //local barrel handle

};
