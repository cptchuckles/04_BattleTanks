// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	ATank* ThisTank;
	ATank* Target;
	
	ATank* GetPlayerTank();
	
	UPROPERTY(EditAnywhere, Category = "Navigation")
	float AcceptanceRadius = 1000.f; //30m acceptance radius for pathfinding, assuming cm
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	
	
};
