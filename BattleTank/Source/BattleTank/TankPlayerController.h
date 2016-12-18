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
    
    // return true if hit landscape, by-ref filling oif 3d worldspace coords
    bool GetSightRayHitLocation( FVector& OutLocation ) const;
    
    // get the direction that the crosshair is "looking" in as a unit vector
    bool GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const;
    
    // perform line trace along look direction ( per crosshair ) and see what we hit
    bool GetLookVectorHitLocation ( FVector LookDirection, FVector& WorldHitLocation ) const;
    
private:

    ATank* ControlledTank = nullptr;
    float TickTime = 0.0f;

    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5; // coincides with PlayerUI_BP that anchors crosshair to halfway horizontally
    
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333; // coincides with PlayerUI_BP that anchors crosshair to 1/3 from the top
    
    // range in cm 10k == 1000000cm
    UPROPERTY(EditAnywhere)
    float MaxRange = 1000000.0;
    
};
