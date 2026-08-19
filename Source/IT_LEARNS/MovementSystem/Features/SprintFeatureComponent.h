// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IT_LEARNS/MovementSystem/MovementFeatureComponent.h"
#include "SprintFeatureComponent.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IT_LEARNS_API USprintFeatureComponent : public UMovementFeatureComponent
{
	GENERATED_BODY()

public:
	USprintFeatureComponent();
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum 
		ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	virtual void ActivateFeature() override;
	virtual void DeactivateFeature() override;
	virtual bool CanActivateFeature() const override;
	virtual bool IsFeatureActivated() const override;
	virtual EMovementFeature GetFeatureType() const override;
	
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> MovementComponent;
	
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true),
		meta=(ClampMin=1))
	float SprintSpeed;
	
	UPROPERTY(EditAnywhere, Category = "Movement", meta=(AllowPrivateAccess=true))
	float InterpSpeed;
	
	float DefaultCharacterSpeed;
	float TargetSpeed;
	bool bSprinting = false;
};
