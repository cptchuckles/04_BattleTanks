// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::TurnTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
    auto DeltaTurn = MaxTurnDegreesPerSecond * RelativeSpeed * GetWorld()->DeltaTimeSeconds;
    SetRelativeRotation(FRotator(0.f, RelativeRotation.Yaw + DeltaTurn, 0.f));
}
