// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EMovementFeature.h"
#include "Components/ActorComponent.h"
#include "MovementFeatureComponent.generated.h"

UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IT_LEARNS_API UMovementFeatureComponent : public UActorComponent
{
	GENERATED_BODY()

public: 
	UMovementFeatureComponent();
	
	virtual void ActivateFeature();
	virtual void DeactivateFeature();
	virtual bool IsFeatureActivated() const;
	
	//Tell which movement feature children classes are
	virtual EMovementFeature GetFeatureType() const PURE_VIRTUAL(
		UMovementFeatureComponent::GetFeatureType,
		return EMovementFeature::None;
		); 
	
protected: 
	virtual bool CanActivateFeature() const ;
};