// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class ATank;
class UTankTrackComponent;

/**
 * Responsible for driving the tank tracks
 */
UCLASS()
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UTankMovementComponent();

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void IntendMoveForward(float Throw);
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void IntendTurnRight(float Throw);
	UFUNCTION( BlueprintCallable, Category = "Setup" )
	void Initialize(UTankTrackComponent* LeftTrackToSet, UTankTrackComponent* RightTrackToSet);
	
private:
	UTankTrackComponent* LeftTrack = nullptr;
	UTankTrackComponent* RightTrack = nullptr;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	ATank* MyTank = nullptr;
	
};
