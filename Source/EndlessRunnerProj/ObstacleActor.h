// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCheckObject, float, ActorId);
UCLASS()

class ENDLESSRUNNERPROJ_API AObstacleActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AObstacleActor();

	UFUNCTION(BlueprintCallable)
	void BroadcastObstacleReachEnd();	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FCheckObject OnObstacleReachEnd;
	
	FVector MovementDir;
	float Speed;
};

