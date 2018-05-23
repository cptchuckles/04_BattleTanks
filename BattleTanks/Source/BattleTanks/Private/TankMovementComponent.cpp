// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Tank.h"
#include "TankTrackComponent.h"

UTankMovementComponent::UTankMovementComponent()
{
    MyTank = Cast<ATank>(GetOwner());
}

void UTankMovementComponent::Initialize(UTankTrackComponent* LeftTrackToSet, UTankTrackComponent* RightTrackToSet)
{
    if(!(LeftTrackToSet && RightTrackToSet)) return;
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    AActor* Owner = GetOwner();
    auto MoveNorm = MoveVelocity.GetSafeNormal();
    
    auto Front = Owner->GetActorForwardVector().GetSafeNormal();
    float ForwardThrow = FVector::DotProduct(Front, MoveNorm);
    IntendMoveForward(ForwardThrow*0.4f);
    
    auto Cross = FVector::CrossProduct(Front, MoveNorm);
    float RightThrow = Cross.Z;
    IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    Throw = FMath::Clamp(Throw, -1.f, 1.f);
    
    if(!(LeftTrack && RightTrack)) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    Throw = FMath::Clamp(Throw, -1.f, 1.f);
    
    if(!(LeftTrack && RightTrack)) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}
