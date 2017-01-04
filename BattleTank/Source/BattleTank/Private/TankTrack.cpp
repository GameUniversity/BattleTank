// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}


void UTankTrack::BeginPlay()
{
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit );
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                         FActorComponentTickFunction *ThisTickFunction)
{
    // Tank velocity is assumed to be the same as the track velocity
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity() );

    // work-out the required acceleration to negate this
    auto CorrectionAcceleration = - (SlippageSpeed / DeltaTime * GetRightVector() );
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

    // 1/2 of the force required per track ( F = M * a )
    auto CorrectionForce = ( TankRoot->GetMass() * CorrectionAcceleration )/ 2;

    TankRoot->AddForce(CorrectionForce);

}

void UTankTrack::OnHit (
             UPrimitiveComponent* HitComponent,
             AActor* OtherActor,
             UPrimitiveComponent* OtherComponent,
             FVector NormalImpulse,
             const FHitResult& Hit
            )
{
    UE_LOG(LogTemp, Warning, TEXT("%s -> %s on the ground"), *GetOwner()->GetName(), *GetName() );
}

void UTankTrack::SetThrottle(float Throttle)
{
    auto Name = GetName();
    
    // TODO clamp actual throttle value so player can't over-drive
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    
}

