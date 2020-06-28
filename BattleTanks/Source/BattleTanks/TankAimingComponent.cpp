// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld()->GetTimeSeconds() < FireTime + ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Ready;
	}
}

void UTankAimingComponent::Initialize (UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	//TODO figure out Abs
	//TODO let AI fire even if off by a little (currently not good when close)
	if(DeltaRotator.Pitch  > 1.f || DeltaRotator.Yaw > 1.f || DeltaRotator.Pitch  < -1.f || DeltaRotator.Yaw < -1.f)
	{
		return true;
	}
	return false;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if(!Barrel){return;}
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
			(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0.f,
			0.f,
			ESuggestProjVelocityTraceOption::DoNotTrace
			)
		)
	{
	FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

	MoveBarrel(AimDirection);

	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	
	FRotator CurrentRotation = Barrel->GetForwardVector().Rotation();
	FRotator TargetRotation = AimDirection.Rotation();
	DeltaRotator = TargetRotation - CurrentRotation;

	if (DeltaRotator.Yaw > 180) {DeltaRotator.Yaw -= 360;} //To avoid turning the wrong way
	if (DeltaRotator.Yaw < -180) {DeltaRotator.Yaw += 360;} //To avoid turning the wrong way

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);


}


void UTankAimingComponent::Fire()
{
	
	if(!Barrel){return;}
	if(FiringState == EFiringState::Reloading){return;}
	if(MainAmmoCount <= 0){return;}

	FVector SpawnLocation = Barrel->GetSocketLocation("Projectile");
	FRotator SpawnRotation = Barrel->GetForwardVector().Rotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint , SpawnLocation, SpawnRotation);

	if(!Projectile){return;}
	Projectile->LaunchProjectile(LaunchSpeed);

	MainAmmoCount -= 1;
	FireTime = GetWorld()->GetTimeSeconds();
}