// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IT_LEARNS/MovementSystem/MovementFeatureComponent.h"
#include "LeanFeatureComponent.generated.h"


class UCameraComponent;
/**
 * 
 */
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class IT_LEARNS_API ULeanFeatureComponent : public UMovementFeatureComponent
{
	GENERATED_BODY()
	
public:
	ULeanFeatureComponent();
	
	UFUNCTION(BlueprintCallable)
	void SetLeanPivot(USceneComponent* LeanPivot);
	
	//Knowing if the leaning is right or left 
	UFUNCTION(BlueprintCallable)
	void SetLeanInput(float LeanDirection);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, 
		enum ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UFUNCTION(BlueprintCallable, Category="Lean", meta=(AllowPrivateAccess=true))
	virtual void ActivateFeature() override;
	
	UFUNCTION(BlueprintCallable, Category="Lean", meta=(AllowPrivateAccess=true))
	virtual void DeactivateFeature() override;
	
	virtual bool CanActivateFeature() const override;
	virtual bool IsFeatureActivated() const override;
	virtual EMovementFeature GetFeatureType() const override;
	
	UPROPERTY()
	TObjectPtr<USceneComponent> OwningLeanPivot = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category=Lean, meta=(AllowPrivateAccess=true))
	float LeanInterpSpeed = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category=Lean, meta=(AllowPrivateAccess=true),
		meta=(ClampMin=10))
	float LeanAngle = 10.f;
	
	UPROPERTY(EditDefaultsOnly, Category=Lean, meta=(AllowPrivateAccess=true))
	float LeanDistance = 15.f;
	
	UPROPERTY()
	TObjectPtr<UCameraComponent> OwningCameraComponent = nullptr;
	
	bool bLeaning = false;
	float CurrentLeanRoll = 0.f;
	float LeanDirection = 0.0f;
	FVector DefaultLeanLocation;
};
