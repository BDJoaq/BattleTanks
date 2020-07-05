// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "ProjectileFireComponent.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    FiringComponent = GetPawn()->FindComponentByClass<UProjectileFireComponent>();

}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (!InPawn) {return;}

    ATank* PossesedTank = Cast<ATank>(InPawn);

    PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
    
}

void ATankAIController::OnPossesedTankDeath()
{
    GetPawn()->DetachFromControllerPendingDestroy();
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
    
    MoveToActor(PlayerTank, ClosestDistance);
}
