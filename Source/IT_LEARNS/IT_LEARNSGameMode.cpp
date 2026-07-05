// Copyright Epic Games, Inc. All Rights Reserved.

#include "IT_LEARNSGameMode.h"
#include "IT_LEARNSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIT_LEARNSGameMode::AIT_LEARNSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
