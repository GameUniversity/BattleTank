// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; 
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet )
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed )
{

    // if we have no barrel, there is no point
    if ( ! ensure(Barrel) ) { return; }
    
    // if we have no turret, there is no point
    if ( ! ensure(Turret) ) { return; }
    
    auto Time = GetWorld()->GetTimeSeconds();
    auto Me = GetOwner()->GetName();
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
    (
        this,
        OutLaunchVelocity,
        StartLocation,
        TargetLocation,
        LaunchSpeed,
        false,
        0,
        0,
        ESuggestProjVelocityTraceOption::DoNotTrace
    );
    
    
    // calculate the OutLaunchVelocity
    if ( bHaveAimSolution )
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards( AimDirection );
    }

}

void UTankAimingComponent::MoveBarrelTowards( FVector AimDirection )
{

    if ( ! ensure(Barrel && Turret) ) { return; }
    
    // work out difference between current barrel rotation, and AimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate( DeltaRotator.Pitch );
    Turret->Rotate( DeltaRotator.Yaw );

}






