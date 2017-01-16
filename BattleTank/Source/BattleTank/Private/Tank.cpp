// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"

// private members
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

float ATank::TakeDamage
(
         float DamageAmount,
         struct FDamageEvent const & DamageEvent,
         class AController * EventInstigator,
         AActor* DamageCauser
)
{
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp<int32>(DamageAmount,0, CurrentHealth );
    
    CurrentHealth-=DamageToApply;
    
    // perform any death sequence if necessary
    if ( CurrentHealth <= 0 )
    {
        UE_LOG(LogTemp, Warning, TEXT("%s Tank Dies"), *GetName());
    }
    
    
    // update current health state
    float LocalHP = GetHealthPercent();
    UE_LOG(LogTemp, Warning, TEXT("    %s Health Percent : %.2f"), *GetName(), LocalHP);
    if ( LocalHP <= HealthThresholdDead )
    {
        TankHealthState = ETankHealthState::Dead;
        //UE_LOG(LogTemp, Warning, TEXT("    %s SET DEAD"), *GetName());
    }
    else if ( LocalHP <= HealthThresholdCritical )
    {
        TankHealthState = ETankHealthState::Critical;
        //UE_LOG(LogTemp, Warning, TEXT("    %s SET CRITICAL"), *GetName());
    }
    else if ( LocalHP <= HealthThresholdDamaged )
    {
        TankHealthState = ETankHealthState::Damaged;
        //UE_LOG(LogTemp, Warning, TEXT("    %s SET DAMAGED"), *GetName());
    }
    else
    {
        TankHealthState = ETankHealthState::Green;
        //UE_LOG(LogTemp, Warning, TEXT("    %s SET GREED"), *GetName());
    }

    
    return DamageToApply;
}

float ATank::GetHealthPercent() const
{
    return (float)CurrentHealth / (float)StartingHealth;
}


