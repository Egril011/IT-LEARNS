// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "GameFramework/Character.h"
#include "Interface/Interactable.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetOwner()))
		return;
	
	OwningCharacter = Cast<ACharacter>(GetOwner());
}

void UInteractionComponent::Interact()
{
	if (!IsValid(OwningCharacter))
		return;
	
	AActor* InteractableActor = nullptr;
	
	if (!IsItemInteractable(InteractableActor))
		return;
	
	IInteractable::Execute_Interact(
		InteractableActor,
		OwningCharacter);
}

bool UInteractionComponent::PerformInteractionTrace(FHitResult& OutHit) const
{
	if (!IsValid(OwningCharacter) || !IsValid(GetWorld()))
		return false;

	const FVector TraceStart = OwningCharacter->GetActorLocation();
	const FVector TraceEnd = TraceStart + OwningCharacter->GetActorForwardVector() * LineTraceDistancePower;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwningCharacter);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		OutHit,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		Params);
	
	//Debug
	DrawDebugLine(
		GetWorld(),
		TraceStart,
		TraceEnd,
		bHit ? FColor::Green : FColor::Red, 
		false,
		25.f,
		0,
		2.0);
	
	return bHit;
}

bool UInteractionComponent::IsItemInteractable(AActor*& InteractableActor) const
{
	FHitResult Hit;

	const bool bHit = PerformInteractionTrace(Hit);
	if (!bHit)
		return false;
	
	InteractableActor = Hit.GetActor();
	
	return InteractableActor->Implements<UInteractable>();
}
