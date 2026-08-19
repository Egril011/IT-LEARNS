// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementFeatureComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UMovementFeatureComponent::UMovementFeatureComponent()
{
}

void UMovementFeatureComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetOwner()))
		return;
	
	OwningCharacter = Cast<ACharacter>(GetOwner());
}

bool UMovementFeatureComponent::CanActivateFeature() const
{
	return true;
}

void UMovementFeatureComponent::ActivateFeature()
{
}

void UMovementFeatureComponent::DeactivateFeature()
{
}

bool UMovementFeatureComponent::IsFeatureActivated() const
{
	return true;
}