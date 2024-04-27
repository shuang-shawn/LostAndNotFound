// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandle = GetPhysicsHandle();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

	// ...
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle()
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Display, TEXT("Attempting Grabbing"));
	if(PhysicsHandle && GetGrabbableInReach(HitResult))
	{
		UE_LOG(LogTemp, Display, TEXT("Grabbing stuff"));
		HitResult.GetComponent()->SetSimulatePhysics(true);
		HitResult.GetComponent()->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}


bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

}

void UGrabber::Release()
{
	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		HitResult.GetComponent()->SetSimulatePhysics(true);
		HitResult.GetComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}
