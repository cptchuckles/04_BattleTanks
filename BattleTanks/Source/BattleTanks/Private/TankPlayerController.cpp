// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    auto MyTank = Cast<ATank>(GetPawn());
    if(MyTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player %s got tank %s"), *GetName(), *(MyTank->GetName()));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Player %s didn't got tank"), *GetName());
    }
}

