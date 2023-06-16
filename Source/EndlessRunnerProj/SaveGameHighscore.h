// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameHighscore.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERPROJ_API USaveGameHighscore : public USaveGame
{
	GENERATED_BODY()

	
public:

	USaveGameHighscore();
	
	UPROPERTY(EditAnywhere)
	TArray<int> HighScores;
	
};
