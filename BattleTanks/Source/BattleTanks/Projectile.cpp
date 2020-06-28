// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "ProjectileFireComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileFireComponent = CreateDefaultSubobject<UProjectileFireComponent>(FName("Projectile Component"));
	ProjectileFireComponent->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	ProjectileFireComponent->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileFireComponent->Activate();
}