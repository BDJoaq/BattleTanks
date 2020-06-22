// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	SetupInputComponent();

	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATank::SetBarrelReference (UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	TankBarrel = BarrelToSet;
}

void ATank::SetTurretReference (UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation) const
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetupInputComponent()
{
	TankInputComponent = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UInputComponent>();

	if(!InputComponent){return;}
	TankInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Boom."));
	if(!TankBarrel){return;}

	FVector SpawnLocation = TankBarrel->GetSocketLocation("Projectile");
	FRotator SpawnRotation = TankBarrel->GetForwardVector().Rotation();

	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint , SpawnLocation, SpawnRotation);
	
}