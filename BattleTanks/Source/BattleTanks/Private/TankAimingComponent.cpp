// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

const UTankBarrel* UTankAimingComponent::GetBarrel() { return Barrel == nullptr ? nullptr : const_cast<const UTankBarrel*>(Barrel); }
const UTankTurret* UTankAimingComponent::GetTurret() { return Turret == nullptr ? nullptr : const_cast<const UTankTurret*>(Turret); }

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Cast<ATank>(GetOwner())->SetTankAimingComponent(this);
	
	SetBarrelReference(BarrelToSet);
	SetTurretReference(TurretToSet);
}


void UTankAimingComponent::DoTheAim(const FVector& HitLocation, const float LaunchSpeed)
{
	if(!Barrel) {
		UE_LOG(LogTemp, Warning, TEXT("%s has no Barrel reference"), *GetName());
		return;
	}
	
	if(!Turret) {
		UE_LOG(LogTemp, Warning, TEXT("%s has no Turret reference"), *GetName());
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
	
	FString DebugMsg;
	if(bHaveAimSolution)
	{
		auto ShotNormal = OutShotVelocity.GetSafeNormal();
		
		MoveBarrelTowards(ShotNormal);
		
		DebugMsg = GetOwner()->GetName() + FString(" aiming at " + HitLocation.ToString());
	} else {
		DebugMsg = GetOwner()->GetName() + FString(" doesn't have aim solution");
	}
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage((int32)GetOwner()->GetUniqueID(), 15.0f, FColor::Yellow, *DebugMsg);
}


void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	auto BarrelDirection = Barrel->GetForwardVector();	
	
	/*
	//AimDirection is worldspace, we need to adjust it for local space
	auto TankPitchRoll = GetOwner()->GetActorRotation();
	TankPitchRoll.Yaw = 0.f;
	auto LocalAimDir = TankPitchRoll.RotateVector(AimDirection);
	*/
	
	auto DeltaRotator = FQuat::FindBetweenVectors(BarrelDirection, AimDirection).Rotator();
	
	//yaw turret, pitch barrel
	Turret->TurnTurret(DeltaRotator.Yaw);
	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	
	/*
	//draw original aim line
	DrawDebugLine(
		GetWorld(),
		Barrel->GetSocketLocation(FName("Muzzle")),
		Barrel->GetSocketLocation(FName("Muzzle")) + AimDirection*500,
		FColor::Red,
		false
	);
	
	//draw the "local" aim line
	DrawDebugLine(
		GetWorld(),
		Turret->GetSocketLocation(FName("Barrel")),
		Turret->GetSocketLocation(FName("Barrel")) + LocalAimDir*800,
		FColor::Yellow,
		false
	);
	
	//draw the horizontal line
	BarrelDirection.Z = 0.f;
	DrawDebugLine(
		GetWorld(),
		Turret->GetSocketLocation(FName("Barrel")),
		Turret->GetSocketLocation(FName("Barrel")) + BarrelDirection*1000,
		FColor::Blue,
		false
	);
	*/
}

