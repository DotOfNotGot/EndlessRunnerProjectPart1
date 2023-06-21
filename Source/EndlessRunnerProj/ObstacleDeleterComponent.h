// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObstacleDeleterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDLESSRUNNERPROJ_API UObstacleDeleterComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float ObstacleDistanceCheck = 1000.0f;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> IgnoredActors;

	UFUNCTION(BlueprintCallable)
	void GetObstacle();
	
public:	
	// Sets default values for this component's properties
	UObstacleDeleterComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
