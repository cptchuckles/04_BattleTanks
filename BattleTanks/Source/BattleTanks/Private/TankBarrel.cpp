// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
    //step barrel towards AimDirection given max speeds
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto DeltaElevation = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + DeltaElevation;
	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, MinElevation, MaxElevation), 0.f, 0.f));
	
	//check for a threshhold and then say clear to fire
	//UE_LOG(LogTemp, Warning, TEXT("UTankBarrel::ElevateBarrel call made"));
}
