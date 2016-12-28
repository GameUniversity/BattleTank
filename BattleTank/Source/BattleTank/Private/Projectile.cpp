// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    // we want to create the movement component but not to take effect right away
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    ProjectileMovementComponent->bAutoActivate = false;
    

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectile::LaunchProjectile(float Speed)
{
    UE_LOG(LogTemp, Warning, TEXT("LaunchProjectile at %f"), Speed);
    ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed );
    ProjectileMovementComponent->Activate();
}

