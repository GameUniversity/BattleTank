// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
    
    // how close the tank needs to get to the target in cm
    float AcceptanceRadius = 3000;
};
