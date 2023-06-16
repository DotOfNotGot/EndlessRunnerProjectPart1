// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RunnerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERPROJ_API URunnerGameInstance : public UGameInstance
{
	GENERATED_BODY()

	URunnerGameInstance();
	
	FString SaveSlotName;
	
	virtual void Init() override;
	
};
