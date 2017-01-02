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
    Locked
};

// forward declaration
class UTankBarrel;
class UTankTurret;

// Holds Barrel Properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	    
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet );
    void AimAt(FVector HitLocation);
    

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State" )
    EFiringState FiringState = EFiringState::Reloading;
	
private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4500.0;
    
    void MoveBarrelTowards( FVector AimDirection );
    
};
