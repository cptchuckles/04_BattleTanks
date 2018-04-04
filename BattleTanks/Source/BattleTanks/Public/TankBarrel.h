// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//RelativeSpeed should be a value between -1 and 1
	void ElevateBarrel(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 5.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevation = 35.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevation = 0.f;
};
