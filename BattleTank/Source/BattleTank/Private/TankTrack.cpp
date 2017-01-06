// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}


void UTankTrack::BeginPlay()
{
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit );
}

void UTankTrack::OnHit (
             UPrimitiveComponent* HitComponent,
             AActor* OtherActor,
             UPrimitiveComponent* OtherComponent,
             FVector NormalImpulse,
             const FHitResult& Hit
            )
{
    DriveTrack();
    ApplySidewaysForce();
    CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
    // Tank velocity is assumed to be the same as the track velocity
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity() );
    
    // work-out the required acceleration to negate this
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectionAcceleration = - (SlippageSpeed / DeltaTime * GetRightVector() );
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    
    // 1/2 of the force required per track ( F = M * a )
    auto CorrectionForce = ( TankRoot->GetMass() * CorrectionAcceleration )/ 2;
    
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

