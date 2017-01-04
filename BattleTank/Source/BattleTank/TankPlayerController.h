// Copyright Sean Ryan 2016

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward Declarations
class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
    
protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup" )
    void FoundAimingComponent(UTankAimingComponent* AimCompRef );
    

private:

    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
    
    // Move tank barrel toward where the shot would hit
    // where the world intersects with the crosshair
    void AimTowardsCrosshair();
    
//    // return true if hit landscape, by-ref filling oif 3d worldspace coords
//    // DEPRECATED
//    bool GetSightRayHitLocation( FVector& OutLocation ) const;
//    
//    // get the direction that the crosshair is "looking" in as a unit vector
//    bool GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const;
//    
//    // perform line trace along look direction ( per crosshair ) and see what we hit
//    bool GetLookVectorHitLocation ( FVector LookDirection, FVector& WorldHitLocation ) const;
    
    // optimised way of getting crosshair hit
    bool GetCrosshairTraceHit(FString& ObjectHit, FVector& HitLocation ) const;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5; // coincides with PlayerUI_BP that anchors crosshair to halfway horizontally
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333; // coincides with PlayerUI_BP that anchors crosshair to 1/3 from the top
    
    UPROPERTY(EditAnywhere)
    bool DebugTargetting = false;
    
    // range in cm 10k == 1000000cm
    UPROPERTY(EditDefaultsOnly)
    float MaxRange = 1000000.0;
    
};
