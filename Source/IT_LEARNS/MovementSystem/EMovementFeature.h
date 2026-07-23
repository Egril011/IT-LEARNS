// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EMovementFeature.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMovementFeature : uint8
{
	None,
	Walk,
	Sprint,
	Lean
};

