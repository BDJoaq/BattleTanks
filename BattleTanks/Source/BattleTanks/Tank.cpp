// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ATank::TakeDamage (float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamageTaken = FPlatformMath::RoundToInt(DamageAmount);
	
	if (CurrentHealth < DamageTaken) {DamageTaken = CurrentHealth;}
	CurrentHealth -= DamageTaken;

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return CurrentHealth;
}

float ATank::GetHealthPercent() const
{
	return (float) CurrentHealth / (float) StartingHealth;
}