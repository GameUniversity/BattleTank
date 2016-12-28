// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

    // -1 is max counter-clockwise, +1 is max clockwise
    void Rotate ( float RelativeSpeed );
    
private:

UPROPERTY(EditDefaultsOnly, Category = Setup )
float MaxDegreesPerSecond = 20.0;
	
	
};
