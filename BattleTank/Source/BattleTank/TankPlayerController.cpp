// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto AimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if ( ! ensure(AimComponent) ) { return; }
    FoundAimingComponent(AimComponent);
    
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    
    if(InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if ( ! ensure(PossessedTank)) { return; }
        
        // Subscribe our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
        
    }
}

void ATankPlayerController::OnPossessedTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("PLAYER: Tank [ %s ] has died."), *GetPawn()->GetName());
    StartSpectatingOnly();
}


void ATankPlayerController::Tick( float DeltaSeconds )
{
    Super::Tick( DeltaSeconds );
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{

    // depossessing will cause pawn to be missing ergo crashing in pie
    if ( !GetPawn() ) { return; }
    
    auto AimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if ( ! ensure(AimComponent) ) { return; }
    
    // get world location of linetrace through crosshair
    FVector HitLocation = FVector(0);
    FString ObjectHit = "Nothing";
    
    if ( GetCrosshairTraceHit(ObjectHit, HitLocation) )
    {
        AimComponent->AimAt(HitLocation);
    }
    
    if ( DebugTargetting )
    {
        UE_LOG(LogTemp, Warning, TEXT("%s Targetting %s at %s"), *GetPawn()->GetName(), *ObjectHit, *HitLocation.ToString() );
    }

}

// new way
bool ATankPlayerController::GetCrosshairTraceHit(FString& ObjectHit, FVector& HitLocation ) const
{

    // viewport size
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    bool bHit;
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    FHitResult HitResult;
    
    bHit = GetHitResultAtScreenPosition(ScreenLocation, ECollisionChannel::ECC_Camera, false, HitResult);
    
    if ( bHit )
    {
        HitLocation = HitResult.ImpactPoint;
        ObjectHit = HitResult.GetActor()->GetName();
    }
    
    return bHit;
}
