// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	MaxHealthPoints = 3;
	CurrentHealthPoints = MaxHealthPoints;
	
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHealthComponent::BeginPlay()
{
	CurrentHealthPoints = MaxHealthPoints;
	Super::BeginPlay();
}

void UHealthComponent::ModifyHealth(int Value)
{
	if(CurrentHealthPoints + Value > MaxHealthPoints || GetWorld()->GetTimerManager().TimerExists(DamageCooldownTimer))
	{
		return;
	}
	
	CurrentHealthPoints += Value;

	UE_LOG(LogTemp, Warning, TEXT("Current health: %d"), CurrentHealthPoints);
	
	FOnModifyHealth.Broadcast(CurrentHealthPoints);

	GetWorld()->GetTimerManager().SetTimer(DamageCooldownTimer, 0.5f, false);
	
	if(CurrentHealthPoints == 0)
	{
		FOnDeath.Broadcast();
	}
	
}

