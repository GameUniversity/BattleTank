// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// enum for tank aiming states
UENUM()
enum class ETankHealthState : uint8
{
    Green,
    Damaged,
    Critical,
    Dead
};

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
    
    virtual float TakeDamage
    (
        float DamageAmount,
        struct FDamageEvent const & DamageEvent,
        class AController * EventInstigator,
        AActor* DamageCauser
    ) override;
    
    // Returns current health as a percentage between 0 and 1
    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealthPercent() const;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State" )
    ETankHealthState TankHealthState = ETankHealthState::Green;

private:
	// Sets default values for this pawn's properties
	ATank();

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100.0;
    
    // while current health percentage is greater than value, consider it status green.
    // @see ETankHealthState
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float HealthThresholdGreen = 0.8;
    
    // while current health percentage is less than HealthThresholdGreen, and greater
    // than HealthThresholdCritical, consider it status Damaged.
    // @see ETankHealthState
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float HealthThresholdDamaged = 0.6;
    
    // while current health percentage is less than HealthThresholdDamaged, and greater
    // than HealthThresholdDead, consider it status Critical.
    // @see ETankHealthState
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float HealthThresholdCritical = 0.4;

    // when life is reduced to less than HealthThresholdDead, consider status Dead
    // note: maybe you can have negative life under certain circumstances?
    // @see ETankHealthState
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float HealthThresholdDead = 0.0;
    
    
    UPROPERTY(VisibleAnywhere, Category = "Health")
    int32 CurrentHealth = StartingHealth;
    
 
    
};
