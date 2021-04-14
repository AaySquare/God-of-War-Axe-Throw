// Copyright Epic Games, Inc. All Rights Reserved.

#include "GodofWarAxeThrowGameMode.h"
#include "GodofWarAxeThrowCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGodofWarAxeThrowGameMode::AGodofWarAxeThrowGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
