// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraActor.h"
#include "CollisionQueryParams.h"
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
    
    FVector HitSpot;
    if(LineTraceTankAim(HitSpot)) UE_LOG(LogTemp, Warning, TEXT("line good, hit: %s"), *(HitSpot.ToString()));
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
