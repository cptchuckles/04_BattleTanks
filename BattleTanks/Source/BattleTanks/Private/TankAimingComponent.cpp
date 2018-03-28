// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::DoTheAim(const FVector& HitLocation, const float LaunchSpeed)
{
	if(!Barrel) {
		UE_LOG(LogTemp, Warning, TEXT("%s has no Barrel reference"), *GetName());
		return;
	}
	
	auto OutShotVelocity = FVector(0.0f);
	auto MuzzleLocation = Barrel->GetSocketLocation(FName("Muzzle"));
	TArray<AActor*> Self; Self.Add( GetOwner() );
	auto bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this, OutShotVelocity, MuzzleLocation, HitLocation, LaunchSpeed,
		false, 0.f,0.f, ESuggestProjVelocityTraceOption::Type::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam, Self, false
	);
	
	if(bHaveAimSolution)
	{
		auto ShotNormal = OutShotVelocity.GetSafeNormal();
		
		MoveBarrelTowards(ShotNormal);
		
		auto DebugMsg = GetOwner()->GetName() + FString(" aiming via " + ShotNormal.ToString());
		if(GEngine)
			GEngine->AddOnScreenDebugMessage((int32)GetOwner()->GetUniqueID(), 15.0f, FColor::Yellow, *DebugMsg);
	}
}


void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	auto AimAsRotator = AimDirection.Rotation();
	
	//get orientation of barrel and difference
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->ElevateBarrel(5.0f); //TODO: remove magic number
}

