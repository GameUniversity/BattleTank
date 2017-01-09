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
    LastFireTime = GetWorld()->GetTimeSeconds();
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                         FActorComponentTickFunction *ThisTickFunction)
{

    if ( AmmoCount <= 0 )
    {
        FiringState = EFiringState::OutOfAmmo;
        AmmoCount = 0;
    }
    else if ( (GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds )
    {
        FiringState = EFiringState::Reloading;
    }
    else if ( IsBarrelMoving() )
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }

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
        AimingDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards( AimingDirection );
    }

}

void UTankAimingComponent::MoveBarrelTowards( FVector AimDirection )
{

    if ( ! ensure(Barrel && Turret) ) { return; }
    
    // AimingDirection = AimDirection;
    
    // work out difference between current barrel rotation, and AimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate( DeltaRotator.Pitch );
    
    auto Yaw = DeltaRotator.Yaw;
    if ( FMath::Abs(Yaw) > 180 )
    {
        if ( Yaw > 0 )
        {
            Yaw = ( 360 - Yaw ) * -1;
        }
        else
        {
            Yaw = 360 - ( Yaw * -1 );
        }
    }
    Turret->Rotate( Yaw );

}

bool UTankAimingComponent::IsBarrelMoving()
{

    // if we have no barrel, it can't exactly be moving
    if ( !ensure(Barrel) ) { return false; }
    
    auto BarrelForward = Barrel->GetForwardVector();
    
    return !BarrelForward.Equals(AimingDirection, 0.1);
}

void UTankAimingComponent::Fire()
{
    
    if (  FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming )
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
        LastFireTime = GetWorld()->GetTimeSeconds();
        
        // decrease ammo when we fire
        --AmmoCount;
    }
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

int UTankAimingComponent::GetAmmoCount() const
{
    return AmmoCount;
}






