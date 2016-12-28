// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"


// public members
void ATank::AimAt(FVector HitLocation)
{
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed );
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    TankAimingComponent->SetBarrelReference(BarrelToSet);
    Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
    TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
    UE_LOG(LogTemp, Warning, TEXT("Fire Event"));
    
    if ( ! Barrel ) { return; }
    
    // spawn projectile at the socket location in the barrel
    GetWorld()->SpawnActor<AProjectile>(
        ProjectileBlueprint,
        Barrel->GetSocketLocation(FName("Projectile")),
        Barrel->GetSocketRotation(FName("Projectile"))
    );
    
}



// private members
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

