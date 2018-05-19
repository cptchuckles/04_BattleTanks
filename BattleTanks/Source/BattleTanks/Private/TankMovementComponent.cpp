// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Tank.h"

UTankMovementComponent::UTankMovementComponent()
{
    MyTank = Cast<ATank>(GetOwner());
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    Throw = FMath::Clamp(Throw, -1.f, 1.f);
    
    
    UE_LOG(LogTemp, Warning, TEXT("%s at throw %f"), *GetName(), Throw);
}

