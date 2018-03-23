// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    MyTank = Cast<ATank>(GetPawn());
    if(MyTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player %s got tank %s"), *GetName(), *(MyTank->GetName()));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Player %s didn't got tank"), *GetName());
    }
}

ATank* ATankPlayerController::GetTank()
{
    if(MyTank) return MyTank;
    return nullptr;
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    FVector AimDirection = FVector(0.0f);
    GetAimDirection(AimDirection);
    
    UE_LOG(LogTemp, Warning, TEXT("Aim Direction: %s"), *(AimDirection.ToString()));
}

bool ATankPlayerController::GetAimDirection(FVector& OutAimDirection) const
{    
    //get rasterized crosshair coordinates
    int32 cx,cy;
    GetViewportSize(cx, cy);
    float cfx = cx * CrosshairX;
    float cfy = cy * CrosshairY;
    FVector wl;                                                           //wl is garbage
    return DeprojectScreenPositionToWorld(cfx,cfy, wl, OutAimDirection);  //got AimDirection
}
