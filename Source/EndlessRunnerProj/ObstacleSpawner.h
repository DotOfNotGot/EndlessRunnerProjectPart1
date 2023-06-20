// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
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

	TMap<float, TObjectPtr<ATile>> ObstacleDict;

	UFUNCTION()
	void DeleteTile(float ObstacleId);

private:
	TArray<ATile*> CurrentTiles;

	void MoveTiles(float DeltaTime);

	int AmountOfTilesCleared = 0;

	int TilesClearedForSpeedUp = 2;
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

	FOnScoreIncreased FOnScoreIncreased;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ATile>> TilesToPick;

	UPROPERTY(EditAnywhere)
	float TileLength = 10000.0f;
	
	UPROPERTY(EditAnywhere)
	float Speed;
	
	UPROPERTY(EditAnywhere)
	ATile* StartTile;

	TSubclassOf<ATile> GetRandomTileToSpawn();
	
	UFUNCTION(BlueprintCallable)
	void SpawnObstacle();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float DistanceTraveled;
	
	int Points;

	UPROPERTY(EditAnywhere, SaveGame)
	TArray<int> HighScores;

private:
	UFUNCTION()
	void SetHighScores();
	void LoadHighScores();
};
