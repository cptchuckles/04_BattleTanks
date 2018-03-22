// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    MyTank = Cast<ATank>(GetPawn());
    if(MyTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player %s got tank %s"), *GetName(), *(MyTank->GetName()));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Player %s didn't got tank"), *GetName());
    }
}
