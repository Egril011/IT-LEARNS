// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementFeatureManager.generated.h"

class UMovementFeatureComponent;
class USprintFeatureComponent;
enum class EMovementFeature : uint8;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IT_LEARNS_API UMovementFeatureManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementFeatureManager();
	
	virtual void BeginPlay() override;
	
	bool TryActivateFeature(EMovementFeature MovementFeature);
	bool TryDeactivateFeature(EMovementFeature MovementFeature);
	bool IsFeatureActivated(EMovementFeature MovementFeature) const;

private:
	TMap<EMovementFeature, TObjectPtr<UMovementFeatureComponent>> MovementFeatures;
	
	//Finding if the key exists into 'MovementFeatures' 
		//if that is the case return the component
	UMovementFeatureComponent* IsValidMovementFeature(EMovementFeature MovementFeature) const;
};