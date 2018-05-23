// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
//#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->DoTheAim(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	auto GameTime = GetWorld()->GetTimeSeconds();
	bool isLoaded = (GameTime - LastFireTime) >= ShellLoadDelay;
	if(!Barrel || !isLoaded) return;
	LastFireTime = GameTime;
	
	auto Projectile = GetWorld()->SpawnActor<AProjectile>
	(
		ProjectileBP,
		Barrel->GetSocketLocation(FName("Muzzle")),
		Barrel->GetSocketRotation(FName("Muzzle"))
	);
		
	if(Projectile){
		Projectile->LaunchProjectile(LaunchSpeed);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("%s failed to fire"), *GetName());		
	}
}
