// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
    // so that first fire is after a reload period
    LastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                         FActorComponentTickFunction *ThisTickFunction)
{
    if ( (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds )
    {
        FiringState = EFiringState::Reloading;
    }
    
    // TODO Handle aiming and locked states

}


void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet )
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector TargetLocation)
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

void UTankAimingComponent::Fire()
{
    
    if (  FiringState != EFiringState::Reloading )
    {
        if ( ! ensure(Barrel) ) { return; }
        if ( ! ensure(ProjectileBlueprint) ) { return; }
        
        // spawn projectile at the socket location in the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
              ProjectileBlueprint,
              Barrel->GetSocketLocation(FName("Projectile")),
              Barrel->GetSocketRotation(FName("Projectile"))
        );
        
        Projectile->LaunchProjectile(LaunchSpeed);
    }
}






