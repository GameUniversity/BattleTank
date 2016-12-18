// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    // who are we
    auto ControlledTank = GetControlledTank();
    
    if ( ! GetControlledTank() )
    {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController not possesing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController possesing [ %s ]"), *ControlledTank->GetName());
    }

}

void ATankAIController::Tick( float DeltaSeconds )
{
    Super::Tick( DeltaSeconds );
    
    if ( GetControlledTank() && GetPlayerTank() )
    {
        // TODO Move toward the player

        // Aim toward the player
        GetControlledTank()->AimAt( GetPlayerTank()->GetActorLocation() );

        // Fire if ready

    }
    
}


ATank* ATankAIController::GetPlayerTank() const
{
    auto WorldPlayerController = GetWorld()->GetFirstPlayerController();
    
    // if for some reason there was no controller, we'd crash
    if ( ! WorldPlayerController ) { return nullptr; }
    
    return Cast<ATank>(WorldPlayerController->GetPawn());
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}