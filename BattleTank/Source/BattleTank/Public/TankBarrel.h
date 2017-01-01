// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:

    // -1 is max downard movement, and +1 is max up movement
    void Elevate( float RelativeSpeed );
    
private:

// How many degress the barrel can move per second
UPROPERTY(EditDefaultsOnly, Category = "Setup" )
float MaxDegreesPerSecond = 8.0;

// Minimum elevation in degrees
UPROPERTY(EditDefaultsOnly, Category = "Setup" )
float MinElevationDegrees = 0.0;

// Maximum elevation in degrees
UPROPERTY(EditDefaultsOnly, Category = "Setup" )
float MaxElevationDegrees = 40.0;
	
};
