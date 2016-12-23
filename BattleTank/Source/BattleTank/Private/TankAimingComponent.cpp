// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
    Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed ) const
{

    // if we have no barrel, there is no point
    if ( !Barrel ) { return; }
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    
    FCollisionResponseParams OutCollisionParams;
    TArray< AActor * > ActorsToIgnore;
    
    // calculate the OutLaunchVelocity
    if ( UGameplayStatics::SuggestProjectileVelocity
         (
            this,
            OutLaunchVelocity,
            StartLocation,
            TargetLocation,
            LaunchSpeed,
            false, // High Arc
            0.0, // Collision Radius
            0, // Override Gravity Z 0 == no
            ESuggestProjVelocityTraceOption::DoNotTrace,
            OutCollisionParams, // don't use yet
            ActorsToIgnore,  // don't use yet
            false // draw debug
         )
    )
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        auto TankName = GetOwner()->GetName();
        UE_LOG(LogTemp, Warning, TEXT("%s FIRE %s"), *TankName, *AimDirection.ToString() );
    }
}


