// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h" // for defining tank delegate OnDeath

// depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    
    if(InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if ( ! ensure(PossessedTank)) { return; }
        
        // Subscribe our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
        
    }
}

void ATankAIController::OnPossessedTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("AI: Tank [ %s ] has died."), *GetPawn()->GetName());
    auto ControlledTank = GetPawn();
    if ( !ControlledTank ) { return; }
    ControlledTank->DetachFromControllerPendingDestroy();
}


void ATankAIController::Tick( float DeltaSeconds )
{
    Super::Tick( DeltaSeconds );
    
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();
    
    if ( !( PlayerTank && ControlledTank) ) { return; }

    // Move toward the player
    MoveToActor(PlayerTank, AcceptanceRadius );

    // Aim toward the player
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    
    if ( ! ensure(AimingComponent) ) { return; }

    AimingComponent->AimAt( PlayerTank->GetActorLocation() );

    // if aiming or locked fire state then fire
    if ( AimingComponent->GetFiringState() == EFiringState::Locked )
    {
        // TODO limit firing rate
        AimingComponent->Fire();
    }
}
