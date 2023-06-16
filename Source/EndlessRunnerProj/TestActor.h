// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleActor.h"
#include "GameFramework/Actor.h"
#include "ActorPooler.h"
#include "TestActor.generated.h"


class AObstacleActor;

UCLASS()
class ENDLESSRUNNERPROJ_API ATestActor : public AActor
{
	GENERATED_BODY()

	ActorPooler<AObstacleActor>* ObstaclePool;
	
	TMap<float, TObjectPtr<AObstacleActor>> ObstacleDict;

	UFUNCTION()
	void ReturnObstacleToQueue(float ObstacleId);
	
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

	UPROPERTY(EditAnywhere)
	FVector MinMaxSpawnDelay;

	UPROPERTY(EditAnywhere)
	FVector MinMaxSpawnPosOffset;
	
	UPROPERTY(BlueprintReadWrite)
	float CurrentSpawnDelay;
	
	UPROPERTY(EditAnywhere)
	FVector UniversalMovementDir;
	
	UPROPERTY(EditAnywhere)
	float UniversalSpeed;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AObstacleActor> ObstacleToSpawn;


	
	UFUNCTION(BlueprintCallable)
	void SpawnObstacle();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
