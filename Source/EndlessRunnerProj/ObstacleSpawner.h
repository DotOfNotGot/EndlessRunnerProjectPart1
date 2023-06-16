// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleActor.h"
#include "GameFramework/Actor.h"
#include "ActorPooler.h"
#include "SaveGameHighscore.h"
#include "ObstacleSpawner.generated.h"


// class AObstacleActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreIncreased, int, CurrentScore);

UCLASS()
class ENDLESSRUNNERPROJ_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()

	ActorPooler<AObstacleActor>* ObstaclePool;
	
	TMap<float, TObjectPtr<AObstacleActor>> ObstacleDict;

	TMap<float, TObjectPtr<AObstacleActor>> FloorDict;

	UFUNCTION()
	void ReturnObstacleToQueue(float ObstacleId);

	UFUNCTION()
	void DeleteObstacle(float ObstacleId);

	UFUNCTION()
	void DeleteFloor(float ObstacleId);

public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

	FOnScoreIncreased FOnScoreIncreased;

	
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

	UPROPERTY(EditAnywhere)
	TSubclassOf<AObstacleActor> FloorReference;
	
	UPROPERTY(EditAnywhere)
	bool bUsePooling;
	
	UFUNCTION(BlueprintCallable)
	void SpawnObstacle();

	UFUNCTION(BlueprintCallable)
	void SpawnFloor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int Points;

	UPROPERTY(EditAnywhere, SaveGame)
	TArray<int> HighScores;

private:
	UFUNCTION()
	void SetHighScores();
	void LoadHighScores();
};
