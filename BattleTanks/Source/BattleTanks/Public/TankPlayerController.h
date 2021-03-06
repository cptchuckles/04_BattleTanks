// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	ATank* MyTank = nullptr;
	
	UPROPERTY( EditAnywhere )
	float CrosshairX = 0.5f;
	UPROPERTY( EditAnywhere )
	float CrosshairY = 0.4f;
	UPROPERTY( EditAnywhere )
	float ShootRange = 1000000.0f; // 10km shoot range
	
	void AimTowardsCrosshair();
	bool GetAimDirection(FVector&) const;
	bool LineTraceTankAim(FVector&) const;
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	
	UFUNCTION(BlueprintPure, Category = "Setup")
	ATank* GetControlledTank();
	
};
