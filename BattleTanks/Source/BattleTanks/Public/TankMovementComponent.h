// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UTankMovementComponent();

	UFUNCTION( BlueprintCallable, Category = "Movement" )
	void IntendMoveForward(float Throw);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	ATank* MyTank = nullptr;
	
};