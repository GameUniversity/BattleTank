// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
    ATank* GetControlledTank() const;
    
    // Move tank barrel toward where the shot would hit
    // where the world intersects with the crosshair
    void AimTowardsCrosshair();
    
    ATank* ControlledTank = nullptr;
    float TickTime = 0.0f;
};
