// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementFeatureComponent.h"

// Sets default values for this component's properties
UMovementFeatureComponent::UMovementFeatureComponent()
{
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