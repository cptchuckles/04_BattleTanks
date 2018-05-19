// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

ATank* ATankPlayerController::GetTank()
{
    return MyTank ? MyTank : nullptr;
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!MyTank) return;
    
    FVector HitLocation;
    if(LineTraceTankAim(HitLocation)) MyTank->AimAt(HitLocation);
}

bool ATankPlayerController::LineTraceTankAim(FVector& HitLocation) const
{
    auto AimDirection = FVector(0.0f);
    GetAimDirection(AimDirection);
    
    //get start and end of trace line
    auto CamPos = PlayerCameraManager->GetCameraLocation(); //start
    auto TraceEnd = CamPos + AimDirection*ShootRange;       //end
    
    FHitResult HitResult; //output
    FCollisionQueryParams query;
        query.AddIgnoredActor(MyTank);
    if( GetWorld()->LineTraceSingleByChannel
        (
            HitResult,
            CamPos, TraceEnd,
            ECollisionChannel::ECC_Visibility,
            query
        )
      )
    {
        HitLocation = HitResult.ImpactPoint;
        return true;
    } else {
        HitLocation = FVector(0.0f);
    }
    
    return false;
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
