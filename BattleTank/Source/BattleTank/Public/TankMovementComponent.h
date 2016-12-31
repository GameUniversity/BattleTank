// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward Declarations
class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:

    UFUNCTION(BlueprintCallable, Category = Setup)
    void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet );

    // Indicate the forward/reverse unit scale between -1/+1
    UFUNCTION(BlueprintCallable, Category = Input)
    void IntendMoveForward(float Throw);
    
    UFUNCTION(BlueprintCallable, Category = Input)
    void IntendTurnRight(float Throw);
    
    // TODO check best protection level
    virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


    
private:

    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightTrack = nullptr;
	
};
