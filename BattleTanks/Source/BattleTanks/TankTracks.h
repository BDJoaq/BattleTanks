// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	





public:


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle ();

	void ApplySidewaysForce();
	void GetThrottle (float Throttle);

private:

	UTankTracks();
	
	//Force in Newtons, 40K kilogram tank at 10 m/s^2
	UPROPERTY(EditAnywhere, Category = Control)
	float TankMaxDrivingForce = 25000000;
	float CurrentThrottle = 0.f;

protected:

	virtual void BeginPlay() override;

};
