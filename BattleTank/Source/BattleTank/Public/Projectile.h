// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    void LaunchProjectile(float Speed);
    


protected:

    UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* CollisionMesh = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* LaunchBlast = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* ImpactBlast = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    URadialForceComponent* ExplosionForce = nullptr;
    
    // Number of seconds from the point of impact that the projectile will
    // destroy itself
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float DestroyDelay = 1.0;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float ProjectileDamage = 10.0;
	
    UFUNCTION()
    void OnHit
    (
     UPrimitiveComponent* HitComponent,
     AActor* OtherActor,
     UPrimitiveComponent* OtherComponent,
     FVector NormalImpulse,
     const FHitResult& Hit
     
     );
    
    UFUNCTION()
    void ProjectileExpired();
    
};
