// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "TankAimingComponent.h"
#include "Tank.h"
//#include "ProjectileFireComponent.h"



void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
   

    if(!AimingComponent){return;}
    FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (!InPawn) {return;}

    ATank* PossesedTank = Cast<ATank>(InPawn);

    PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossesedTankDeath);
    
}

void ATankPlayerController::OnPossesedTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("I am dead"));
    StartSpectatingOnly();
    //GetPawn()->DetachFromControllerPendingDestroy(); NOT NEEDED, StartSpectatingOnly() tankes care of this
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimAtCrosshair();
}


void ATankPlayerController::AimAtCrosshair()
{
    if (!GetPawn()){return;}
    FVector HitLocation;
 
    if (GetSightRayHitLocation(HitLocation))
    {
        AimingComponent->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    //Here we will find the crosshair that we know is .5 on the X and .33333 on the Y of the viewport

    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    FVector2D ScreenLocation (ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

    FVector WorldLocation; //not used, just need it for the out param
    FVector WorldDirection;
    FVector HitResultLocation;

    DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection); //returns bool

    OutHitLocation = GetObjectHitLocation(WorldDirection);

    if (OutHitLocation.IsZero()){return false;}

    return true;
}

FVector ATankPlayerController::GetObjectHitLocation(FVector WorldDirection) const
{
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector ObjectHitLocation = StartLocation + (HitRange * WorldDirection);

    FHitResult HitResult;


    GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        ObjectHitLocation,
        ECollisionChannel::ECC_Camera
    );

    return HitResult.Location;
}