// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHudWidget.h"

#include "HealthComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UGameplayHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	UHealthComponent* PlayerHealthComponent = Cast<UHealthComponent>(PlayerCharacter->GetComponentByClass(UHealthComponent::StaticClass()));

	AObstacleSpawner* WorldObstacleSpawner = Cast<AObstacleSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), AObstacleSpawner::StaticClass()));
	
	if(PlayerHealthComponent != nullptr)
	{
		PlayerHealthComponent->FOnModifyHealth.AddDynamic(this, &UGameplayHudWidget::UpdateHealthText);
	}

	if(WorldObstacleSpawner != nullptr)
	{
		WorldObstacleSpawner->FOnScoreIncreased.AddDynamic(this, &UGameplayHudWidget::UpdateScoreText);
	}
	
}

void UGameplayHudWidget::UpdateHealthText(int CurrentHealth)
{
	if(HealthText == nullptr)
	{
		return;
	}

	FString NewHealthText = "Current Health: ";

	NewHealthText.AppendInt(CurrentHealth);
	
	HealthText->SetText(FText::FromString(NewHealthText));
}

void UGameplayHudWidget::UpdateScoreText(int CurrentScore)
{
	if(ScoreText == nullptr)
	{
		return;
	}

	FString NewScoreText = "Score: ";

	NewScoreText.AppendInt(CurrentScore);
	
	ScoreText->SetText(FText::FromString(NewScoreText));
}
