// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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
	auto hit = UGameplayStatics::SuggestProjectileVelocity(
		this, OutShotVelocity, MuzzleLocation, HitLocation, LaunchSpeed,
		false, 0.f,0.f, ESuggestProjVelocityTraceOption::Type::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam, Self, false
	);
	
	auto ShotNormal = OutShotVelocity.GetSafeNormal();
	
	auto DebugMsg = GetOwner()->GetName() + FString(" aiming via " + ShotNormal.ToString() + " -- hit? " + FString::FromInt(hit));
	if(GEngine)
		GEngine->AddOnScreenDebugMessage((int32)GetOwner()->GetUniqueID(), 15.0f, FColor::Yellow, *DebugMsg);
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

