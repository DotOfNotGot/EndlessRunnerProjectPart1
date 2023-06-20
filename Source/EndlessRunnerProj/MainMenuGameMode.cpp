// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

AMainMenuGameMode::AMainMenuGameMode()
{

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	
}
