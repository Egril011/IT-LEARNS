// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintFeatureComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

USprintFeatureComponent::USprintFeatureComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled =false;
}

void USprintFeatureComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetOwningCharacter()))
		return;
	
	MovementComponent = GetOwningCharacter()->GetCharacterMovement();
	DefaultCharacterSpeed = MovementComponent->MaxWalkSpeed;
}

void USprintFeatureComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Increasing or decreasing the character' speed 
	if (!IsValid(MovementComponent))
	{
		SetComponentTickEnabled(false);
		return;
	}

	const float CurrentSpeed = MovementComponent->MaxWalkSpeed;
	const float NewCharacterSpeed = FMath::FInterpTo(CurrentSpeed,
		TargetSpeed, DeltaTime, InterpSpeed);
	
	MovementComponent->MaxWalkSpeed = NewCharacterSpeed;
	
	if (FMath::IsNearlyEqual(NewCharacterSpeed, TargetSpeed, 1.f))
	{
		MovementComponent->MaxWalkSpeed = NewCharacterSpeed;
		SetComponentTickEnabled(false);
	}
}

void USprintFeatureComponent::ActivateFeature()
{
	if (!IsValid(MovementComponent) || !CanActivateFeature())
		return;
	
	TargetSpeed = SprintSpeed;
	SetComponentTickEnabled(true);
}

void USprintFeatureComponent::DeactivateFeature()
{
	if (!IsValid(MovementComponent))
		return;
	
	TargetSpeed = DefaultCharacterSpeed;
	SetComponentTickEnabled(true);
}

bool USprintFeatureComponent::CanActivateFeature() const
{
	if (!IsValid(MovementComponent))
		return false;
	
	return MovementComponent->IsMovingOnGround();
}

bool USprintFeatureComponent::IsFeatureActivated() const
{
	return bSprinting;
}

EMovementFeature USprintFeatureComponent::GetFeatureType() const
{
	return EMovementFeature::Sprint;
}