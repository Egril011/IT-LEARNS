// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementFeatureManager.h"

#include "MovementFeatureComponent.h"

// Sets default values for this component's properties
UMovementFeatureManager::UMovementFeatureManager()
{
}

void UMovementFeatureManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetOwner()))
		return;
	
	//Get all the components, which are attached to the owner, 
		//and add it into the TMap
	TArray<UMovementFeatureComponent*> FeatureComponents;
	GetOwner()->GetComponents<UMovementFeatureComponent>(FeatureComponents);
	
	for (UMovementFeatureComponent* FeatureComponent : FeatureComponents)
	{
		if (!IsValid(FeatureComponent))
			continue;
		
		MovementFeatures.Add(FeatureComponent->GetFeatureType(), FeatureComponent); 
	}
}

bool UMovementFeatureManager::TryActivateFeature(const EMovementFeature MovementFeature)
{
	UMovementFeatureComponent* FeatureComponent = IsValidMovementFeature(MovementFeature);
	if (!IsValid(FeatureComponent))
		return false;
	
	FeatureComponent->ActivateFeature();
	return true;
}

bool UMovementFeatureManager::TryDeactivateFeature(const EMovementFeature MovementFeature)
{
	UMovementFeatureComponent* FeatureComponent = IsValidMovementFeature(MovementFeature);
	if (!IsValid(FeatureComponent))
		return false;
	
	FeatureComponent->DeactivateFeature();
	return true;
}

bool UMovementFeatureManager::IsFeatureActivated(const EMovementFeature MovementFeature) const
{
	const UMovementFeatureComponent* FeatureComponent = IsValidMovementFeature(MovementFeature);
	if (!IsValid(FeatureComponent))
		return false;
	
	return FeatureComponent->IsFeatureActivated();
}

UMovementFeatureComponent* UMovementFeatureManager::IsValidMovementFeature(const EMovementFeature MovementFeature) const
{
	if (!MovementFeatures.Find(MovementFeature))
		return nullptr;

	 UMovementFeatureComponent* FeatureComponent = Cast<UMovementFeatureComponent>(MovementFeatures
		[MovementFeature]);
	
	return FeatureComponent;
}
