// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Ready
};

class AProjectile;
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable)
	void Initialize (UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt (FVector HitLocation);
	void MoveBarrel(FVector AimDirection);	
	bool IsBarrelMoving();


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000;

	UFUNCTION(BlueprintCallable)
	void Fire ();

	UPROPERTY (EditAnywhere, BlueprintReadOnly, Category = "Firing")
	int32 MainAmmoCount = 3;

private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	bool bCanFire = true;
	float FireTime = -5.f;
	FRotator DeltaRotator;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTime = 3.f;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY (BlueprintReadOnly)
	EFiringState FiringState = EFiringState::Ready;
};
