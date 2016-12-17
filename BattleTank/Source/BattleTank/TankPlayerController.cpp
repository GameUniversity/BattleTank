// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    ControlledTank = GetControlledTank();
    
    if ( ! ControlledTank )
    {
        UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possesing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possesing [ %s ]"), *ControlledTank->GetName());
    }

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
    if ( ! ControlledTank ) { return; }
    
    // get world location of linetrace through crosshair
    // if it hits the landscape
        // tell controlled tank to aim at this point

}