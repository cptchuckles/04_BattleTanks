// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"


void UTankTrackComponent::SetThrottle(float Throttle)
{
    Throttle = FMath::Clamp(Throttle, -1.f, 1.f);
    
    auto ForceApplied = GetForwardVector() * TrackMaxForce * Throttle;
    auto ForceLocation = GetComponentLocation();
    
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    
}

