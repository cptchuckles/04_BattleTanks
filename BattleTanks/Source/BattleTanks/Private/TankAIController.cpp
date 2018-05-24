// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    PrimaryActorTick.bCanEverTick = true;
    
    // verify muh tank
    ThisTank = Cast<ATank>(GetPawn());
    if(!ThisTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI %s HAS NO FUCCIN TANK"), *GetName());
        PrimaryActorTick.bCanEverTick = false;
    }
}

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    if(!Target){
        Target = GetPlayerTank();
    } else {
        auto PathfindResult = MoveToActor(
                                            Target,
                                            AcceptanceRadius,
                                            true,
                                            true,
                                            false
                                        );
        
        ThisTank->AimAt(Target->GetActorLocation());
        ThisTank->Fire();
    }
}

ATank* ATankAIController::GetPlayerTank()
{
    auto player1 = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
    if(player1) return player1->GetControlledTank();
    
    UE_LOG(LogTemp, Warning, TEXT("AI %s didn't find player tank"), *GetName());
    return nullptr;
}
