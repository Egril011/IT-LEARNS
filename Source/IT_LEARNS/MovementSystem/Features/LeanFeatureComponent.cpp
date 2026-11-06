// Fill out your copyright notice in the Description page of Project Settings.


#include "LeanFeatureComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

ULeanFeatureComponent::ULeanFeatureComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void ULeanFeatureComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* Character = GetOwningCharacter();
	if (!IsValid(Character))
		return;
	
	OwningCameraComponent = Character->FindComponentByClass<UCameraComponent>();
}

void ULeanFeatureComponent::SetLeanPivot(USceneComponent* LeanPivot)
{
	if (!IsValid(LeanPivot))
		return;
	
	OwningLeanPivot = LeanPivot;
	DefaultLeanLocation = LeanPivot->GetRelativeLocation();
}

void ULeanFeatureComponent::SetLeanInput(const float InLeanDirection)
{
	LeanDirection = FMath::Clamp(InLeanDirection, -1.f, 1.0);
}

void ULeanFeatureComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!IsValid(OwningLeanPivot) || !IsValid(OwningCameraComponent))
	{
		SetComponentTickEnabled(false);
		return;
	}
	
	//Move the LeanPivot and rotate it to create a lean effect due of the camera component his a child of LeanPivot
	const FVector CurrentLeanLocation = OwningLeanPivot->GetRelativeLocation();

	const float TargetLeanRoll = bLeaning ? 
		LeanAngle * LeanDirection: 
		0.f;
	
	FVector TargetLeanPosition = DefaultLeanLocation;
	if (bLeaning)
	{
		TargetLeanPosition.Y += LeanDistance * LeanDirection;
	} 
	
	const FVector NewLeanLocation = FMath::VInterpTo(
		CurrentLeanLocation,
		TargetLeanPosition,
		DeltaTime,
		LeanInterpSpeed);
	
	CurrentLeanRoll = FMath::FInterpTo(
		CurrentLeanRoll,
		TargetLeanRoll,
		DeltaTime,
		LeanInterpSpeed);
	
	const bool bLocationFinished =
		NewLeanLocation.Equals(TargetLeanPosition, 1.f);

	const bool bRotationFinished =
		FMath::IsNearlyEqual(
			CurrentLeanRoll,
			TargetLeanRoll,
			0.1f);
	
	FVector FinalLeanLocation = NewLeanLocation;
	float FinalLeanRoll = CurrentLeanRoll;

	if (bLocationFinished && bRotationFinished)
	{
		FinalLeanLocation = TargetLeanPosition;
		FinalLeanRoll = TargetLeanRoll;
		CurrentLeanRoll = TargetLeanRoll;

		SetComponentTickEnabled(false);
	}

	// Apply lateral camera movement through the pivot.
	OwningLeanPivot->SetRelativeLocation(FinalLeanLocation);

	// Apply roll to the final camera view.
	OwningCameraComponent->ClearAdditiveOffset();

	const FTransform LeanOffset(
		FRotator(0.f, 0.f, FinalLeanRoll),
		FVector::ZeroVector,
		FVector::OneVector);

	OwningCameraComponent->AddAdditiveOffset(
		LeanOffset,
		0.f);
}

void ULeanFeatureComponent::ActivateFeature()
{
	Super::ActivateFeature();
	
	if (!IsValid(OwningLeanPivot)) //|| !IsValid(OwningCameraComponent))
		return;
	
	bLeaning = true;
	//OwningCameraComponent->bUsePawnControlRotation = false;
	SetComponentTickEnabled(true);
}

void ULeanFeatureComponent::DeactivateFeature()
{
	Super::DeactivateFeature();
	
	if (!IsValid(OwningLeanPivot)) //|| !IsValid(OwningCameraComponent))
		return;
	
	bLeaning = false;
	SetComponentTickEnabled(true);
}

bool ULeanFeatureComponent::CanActivateFeature() const
{
	return Super::CanActivateFeature() 
	&& bLeaning 
	&& IsValid(OwningLeanPivot);
}

bool ULeanFeatureComponent::IsFeatureActivated() const
{
	return bLeaning;
}

EMovementFeature ULeanFeatureComponent::GetFeatureType() const
{
	return EMovementFeature::Lean;
}