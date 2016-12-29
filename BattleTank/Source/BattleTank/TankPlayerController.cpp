// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankPlayerController::Tick( float DeltaSeconds )
{
    Super::Tick( DeltaSeconds );
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if ( ! GetControlledTank() ) { return; }
    
    // get world location of linetrace through crosshair
    FVector HitLocation;
    if ( GetSightRayHitLocation(HitLocation) )
    {
        GetControlledTank()->AimAt(HitLocation);
    }

}

bool ATankPlayerController::GetSightRayHitLocation( FVector& OutLocation ) const
{
    // find crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    
    // "De-project" screen position of the crosshair into world direction
    FVector LookDirection;
    if ( GetLookDirection(ScreenLocation, LookDirection) )
    {
        // Line-trace along that look direction and see what we hit up to max range
        GetLookVectorHitLocation(LookDirection, OutLocation);
    }
    
    
    return true;
}

bool ATankPlayerController::GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const
{
    FVector CameraWorldLoc; // discarded
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLoc,
        LookDirection
     );
}


bool ATankPlayerController::GetLookVectorHitLocation ( FVector LookDirection, FVector& HitLocation ) const
{
    
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + ( LookDirection * MaxRange );
    
    if (
        GetWorld()->LineTraceSingleByChannel(
            HitResult,
            StartLocation,
            EndLocation,
            ECollisionChannel::ECC_Visibility
        )
    )
    {
        HitLocation = HitResult.Location;
        return true;
    }
    
    HitLocation = FVector(0.0,0.0,0.0);
    return false;
    
}









