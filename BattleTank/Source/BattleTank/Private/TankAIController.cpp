// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"
// depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaSeconds )
{
    Super::Tick( DeltaSeconds );
    
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ControlledTank = Cast<ATank>(GetPawn());

    if ( ensure(PlayerTank) )
    {
        // Move toward the player
        MoveToActor(PlayerTank, AcceptanceRadius );

        // Aim toward the player
        ControlledTank->AimAt( PlayerTank->GetActorLocation() );

        // Fire if ready
        ControlledTank->Fire(); 

    }
    
}
