// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate (float RelativeSpeed)
{

    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

    float ElevationChange = RelativeSpeed * ElevateSpeed * GetWorld()->DeltaTimeSeconds;
    float NewElevation = FMath::Clamp<float>(GetRelativeRotation().Pitch + ElevationChange, MinPitch, MaxPitch);
   

    SetRelativeRotation (FRotator(NewElevation, 0, 0));


}