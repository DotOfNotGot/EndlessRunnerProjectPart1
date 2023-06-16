// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleSpawner.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameplayHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERPROJ_API UGameplayHudWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AObstacleSpawner> ObstacleSpawnerReference;
	
	UFUNCTION()
	void UpdateHealthText(int CurrentHealth);

	UFUNCTION()
	void UpdateScoreText(int CurrentScore);

	UPROPERTY(meta=(BindWidget))
	UTextBlock* HealthText; 
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreText;
};
