// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERPROJ_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	TArray<UTextBlock*> GetTextBlocksArray();
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreOne; 
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreTwo;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreThree;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreFour;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreFive;
	
};
