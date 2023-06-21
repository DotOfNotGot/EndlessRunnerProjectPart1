// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnModifyHealth, int, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSRUNNERPROJ_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	FOnModifyHealth FOnModifyHealth;

	UPROPERTY(BlueprintAssignable)
	FOnDeath FOnDeath;

	FTimerHandle DamageCooldownTimer;

	virtual void BeginPlay() override;
	
protected:
	// Called when the game starts

public:	
	// Called every frame

	UPROPERTY(EditAnywhere)
	int MaxHealthPoints;

	UPROPERTY()
	int CurrentHealthPoints;

	UFUNCTION(BlueprintCallable)
	void ModifyHealth(int Value);
		
};
