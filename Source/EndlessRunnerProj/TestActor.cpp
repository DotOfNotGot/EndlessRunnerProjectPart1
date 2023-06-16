// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	ObstaclePool = new ActorPooler<AObstacleActor>(GetWorld(),  ObstacleToSpawn);

	ObstaclePool->Populate(50);
	
	CurrentSpawnDelay = FMath::RandRange(MinMaxSpawnDelay.X, MinMaxSpawnDelay.Y);
	
	Super::BeginPlay();
}

void ATestActor::SpawnObstacle()
{
	int spawnAmount = FMath::RandRange(3, 7);
	
	for (int i = 0; i < spawnAmount; i++ )
	{
		TObjectPtr<AObstacleActor> currentObstacle =  ObstaclePool->Pop();
		currentObstacle->OnObstacleReachEnd.AddDynamic(this, &ATestActor::ReturnObstacleToQueue); 

		ObstacleDict.Add(currentObstacle->GetUniqueID(), currentObstacle);

		float currentSpawnPosOffset = FMath::RandRange(MinMaxSpawnPosOffset.X, MinMaxSpawnPosOffset.Y);

		FVector currentPos = this -> GetActorLocation();
	
		currentObstacle -> SetActorLocation(currentPos + FVector(currentSpawnPosOffset,0,0));

		currentObstacle->MovementDir = UniversalMovementDir;
		currentObstacle->Speed = UniversalSpeed;
	}

	UniversalSpeed += 1;

	UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), UniversalSpeed);
	
	CurrentSpawnDelay = FMath::RandRange(MinMaxSpawnDelay.X, MinMaxSpawnDelay.Y);
}


void ATestActor::ReturnObstacleToQueue(float ObstacleId)
{
	ObstaclePool->Enqueue(ObstacleDict[ObstacleId]);
}



// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

