// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTracks.h"



void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{

    FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    FVector MovementVelocity = MoveVelocity.GetSafeNormal();

    float ForwardThrow = FVector::DotProduct(TankForward, MovementVelocity);
    FVector RightThrow = FVector::CrossProduct(TankForward, MovementVelocity);

    IntendMoveForward(ForwardThrow);
    IntendRotateClockwise(RightThrow.Z);
}

void UTankMovementComponent::Initialize (UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{

    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;


}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!LeftTrack || !RightTrack) {return;}

    LeftTrack->GetThrottle(Throw);
    RightTrack->GetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
    if (!LeftTrack || !RightTrack) {return;}

    LeftTrack->GetThrottle(Throw);
    RightTrack->GetThrottle(-Throw);
}