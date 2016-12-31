// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward Declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
    
protected:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    ATank* GetControlledTank() const;
    

private:

    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
    
    // Move tank barrel toward where the shot would hit
    // where the world intersects with the crosshair
    void AimTowardsCrosshair();
    
    // return true if hit landscape, by-ref filling oif 3d worldspace coords
    bool GetSightRayHitLocation( FVector& OutLocation ) const;
    
    // get the direction that the crosshair is "looking" in as a unit vector
    bool GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const;
    
    // perform line trace along look direction ( per crosshair ) and see what we hit
    bool GetLookVectorHitLocation ( FVector LookDirection, FVector& WorldHitLocation ) const;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5; // coincides with PlayerUI_BP that anchors crosshair to halfway horizontally
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333; // coincides with PlayerUI_BP that anchors crosshair to 1/3 from the top
    
    // range in cm 10k == 1000000cm
    UPROPERTY(EditDefaultsOnly)
    float MaxRange = 1000000.0;
    
};
