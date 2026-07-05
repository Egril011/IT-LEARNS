// Copyright Epic Games, Inc. All Rights Reserved.

#include "IT_LEARNSPickUpComponent.h"

UIT_LEARNSPickUpComponent::UIT_LEARNSPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UIT_LEARNSPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UIT_LEARNSPickUpComponent::OnSphereBeginOverlap);
}

void UIT_LEARNSPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AIT_LEARNSCharacter* Character = Cast<AIT_LEARNSCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
