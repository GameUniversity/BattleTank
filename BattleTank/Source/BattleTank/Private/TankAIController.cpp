// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
// depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaSeconds )
{
    Super::Tick( DeltaSeconds );
    
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();
    
    if ( !ensure( PlayerTank && ControlledTank)) { return; }

    // Move toward the player
    MoveToActor(PlayerTank, AcceptanceRadius );

    // Aim toward the player
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    
    if ( ! ensure(AimingComponent) ) { return; }

    AimingComponent->AimAt( PlayerTank->GetActorLocation() );

    // Fire if ready
    // TODO fix firing
    //ControlledTank->Fire();
    
}
