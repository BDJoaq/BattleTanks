// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//class UProjectileFireComponent;
class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	UFUNCTION (BlueprintImplementableEvent)
	void FoundAimingComponent (UTankAimingComponent* AimingComponentRef);


public:
	void AimAtCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	FVector GetObjectHitLocation(FVector WorldDirection) const

	UPROPERTY(EditAnywhere);
	float CrosshairXLocation = .5;

	UPROPERTY(EditAnywhere);
	float CrosshairYLocation = .33333;

	UPROPERTY(EditAnywhere);
	float HitRange = 1000000;

	UTankAimingComponent* AimingComponent = nullptr;
	//UProjectileFireComponent* FiringComponent = nullptr;
};

