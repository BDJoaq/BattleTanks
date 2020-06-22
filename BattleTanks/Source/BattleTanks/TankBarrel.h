// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:

	void Elevate (float RelativeSpeed);

	UPROPERTY(EditAnywhere, Category = Setup)
	float ElevateSpeed = 20.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxPitch = 50;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinPitch = 0;

};
