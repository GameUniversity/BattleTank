// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate( float DegreesPerSecond )
{
    
    // move barrel the right abount this frame given a max elevation speed and frame rate
    UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called with speed %f"), DegreesPerSecond );
    
}
