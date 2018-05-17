// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "TankShellMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetupShellMovementComponent();

}

void AProjectile::SetupShellMovementComponent()
{
	ShellMovement = CreateDefaultSubobject<UTankShellMovementComponent>(FName("ShellMovement"));
	ShellMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProjectile::LaunchProjectile(float Speed)
{
	if(!ShellMovement) {
		UE_LOG(LogTemp, Warning, TEXT("Projectile failed to have shell movement component"));
		SetupShellMovementComponent();
	}
	if(!ShellMovement) return;
	
	ShellMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ShellMovement->Activate();
}

