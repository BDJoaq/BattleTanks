// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "ProjectileFireComponent.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    FiringComponent = GetPawn()->FindComponentByClass<UProjectileFireComponent>();

}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

   if(!GetPawn()||!PlayerTank){return;}
    
    FVector HitLocation = PlayerTank->GetActorLocation();
    AimingComponent->AimAt(HitLocation);

    if (!AimingComponent->IsBarrelMoving())
    {
        AimingComponent->Fire();
    }
    
    MoveToActor(PlayerTank, 1500.f);
}
