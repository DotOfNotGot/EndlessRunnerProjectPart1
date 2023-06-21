// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerProjGameMode.h"
#include "EndlessRunnerProjCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerProjGameMode::AEndlessRunnerProjGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
