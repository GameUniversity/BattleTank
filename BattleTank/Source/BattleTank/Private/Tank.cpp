// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// public members
void ATank::AimAt(FVector HitLocation)
{
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed );
}

void ATank::Fire()
{
    
    bool isReloaded = ( FPlatformTime::Seconds() - LastFireTime ) > ReloadTimeInSeconds;
    
    if ( Barrel && isReloaded )
    {
        // spawn projectile at the socket location in the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            Barrel->GetSocketLocation(FName("Projectile")),
            Barrel->GetSocketRotation(FName("Projectile"))
        );
        
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
}



// private members
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

