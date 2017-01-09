// Copyright Sean Ryan 2016

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// enum for tank aiming states
UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked,
    OutOfAmmo
};

// forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds Barrel Properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	    
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet );
    
    UFUNCTION(BlueprintCallable, Category = "Fire")
    void Fire();
    
    void AimAt(FVector HitLocation);
    
    EFiringState GetFiringState() const;
    
    UFUNCTION(BlueprintCallable, Category = "State" )
    int GetAmmoCount() const;
    
protected:
    UPROPERTY(BlueprintReadOnly, Category = "State" )
    EFiringState FiringState = EFiringState::Reloading;

	
private:
    // Methods
    UTankAimingComponent();
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    
    void MoveBarrelTowards( FVector AimDirection );
    bool IsBarrelMoving();

    // Members
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4500.0;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.0;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int AmmoCount = 5;

    float LastFireTime = 12345.0;
    
    FVector AimingDirection;
    
    
};
