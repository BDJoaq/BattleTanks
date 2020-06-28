// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTracks.h"


UTankTracks::UTankTracks()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTracks::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
	
}

void UTankTracks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    SetThrottle();
    ApplySidewaysForce();
    CurrentThrottle = 0;
}

void UTankTracks::ApplySidewaysForce()
{
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    auto SlippingSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector()); //DotProduct provides Cos of the angles
    auto CorrectionAcceleration = -(SlippingSpeed / DeltaTime) * GetRightVector(); //Negative because the correction will go the opposite way
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //F=M*A we divide by2 b/c there's 2 tracks

    TankRoot->AddForce(CorrectionForce);

}

void UTankTracks::GetThrottle (float Throttle)
{
    CurrentThrottle += Throttle;
    UE_LOG(LogTemp, Warning, TEXT("Made it here"));
}



void UTankTracks::SetThrottle ()
{
    


    FVector ForceApplied = GetForwardVector() * CurrentThrottle * TankMaxDrivingForce;
    FVector ForceLocation = GetComponentLocation();


    UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    

}