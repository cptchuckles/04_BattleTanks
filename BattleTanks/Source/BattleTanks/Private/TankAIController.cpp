// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
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
    
    Target = GetPlayerTank();
    if(Target) ThisTank->AimAt(Target->GetActorLocation());
}

ATank* ATankAIController::GetPlayerTank()
{
    auto player1 = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
    if(player1) return player1->GetTank();
    
    UE_LOG(LogTemp, Warning, TEXT("AI %s didn't find player tank"), *GetName());
    return nullptr;
}

