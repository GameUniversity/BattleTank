// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
    void AimAt(FVector HitLocation);
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetTurretReference(UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = Fire)
    void Fire();
    
protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 4500.0;
    
    UPROPERTY(EditAnywhere, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    // Local barrel reference for spawning projectiles
    UTankBarrel* Barrel = nullptr;
    
    float ReloadTimeInSeconds = 3.0;
    double LastFireTime = 0.0;
	
};
