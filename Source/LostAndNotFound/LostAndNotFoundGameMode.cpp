// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostAndNotFoundGameMode.h"
#include "LostAndNotFoundCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALostAndNotFoundGameMode::ALostAndNotFoundGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
