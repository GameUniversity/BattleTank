// Copyright Sean Ryan 2016

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet )
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if ( ! ensure(LeftTrack && RightTrack) ) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if ( ! ensure(LeftTrack && RightTrack) ) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);    
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    // no super as we are replacing functionality
    
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    
    // use dot product calculate how "forward" we need to move in a smooth fashion.
    // this will be between -1 and +1 to determine how forward we need to move
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    IntendMoveForward(ForwardThrow);
    
    auto TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
    IntendTurnRight(TurnThrow);
    
}

