// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* PCPawn = GetPlayerTank();

    if(PCPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("I see %s"), *PCPawn->GetName());
    }

}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!GetControlledTank()||!GetPlayerTank()){return;}
    
    FVector HitLocation = GetPlayerTank()->GetActorLocation();
    GetControlledTank()->AimAt(HitLocation);
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}