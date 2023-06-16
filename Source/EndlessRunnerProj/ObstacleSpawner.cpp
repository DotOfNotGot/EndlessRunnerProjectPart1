// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"

#include "HealthComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	LoadHighScores();
	
	ObstaclePool = new ActorPooler<AObstacleActor>(GetWorld(), ObstacleToSpawn);

	ObstaclePool->Populate(50);

	CurrentSpawnDelay = FMath::RandRange(MinMaxSpawnDelay.X, MinMaxSpawnDelay.Y);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	UHealthComponent* PlayerHealthComponent = Cast<UHealthComponent>(
		PlayerCharacter->GetComponentByClass(UHealthComponent::StaticClass()));

	if (PlayerHealthComponent != nullptr)
	{
		PlayerHealthComponent->FOnDeath.AddDynamic(this, &AObstacleSpawner::SetHighScores);
	}

	Super::BeginPlay();
}

void AObstacleSpawner::SpawnObstacle()
{
	int spawnAmount = FMath::RandRange(3, 7);

	Points += 100;
	FOnScoreIncreased.Broadcast(Points);


	if (bUsePooling)
	{
		for (int i = 0; i < spawnAmount; i++)
		{
			TObjectPtr<AObstacleActor> currentObstacle = ObstaclePool->Pop();
			currentObstacle->OnObstacleReachEnd.AddDynamic(this, &AObstacleSpawner::ReturnObstacleToQueue);

			ObstacleDict.Add(currentObstacle->GetUniqueID(), currentObstacle);

			float currentSpawnPosOffset = FMath::RandRange(MinMaxSpawnPosOffset.X, MinMaxSpawnPosOffset.Y);

			FVector currentPos = this->GetActorLocation();

			currentObstacle->SetActorLocation(currentPos + FVector(currentSpawnPosOffset, 0, 0));

			currentObstacle->MovementDir = UniversalMovementDir;
			currentObstacle->Speed = UniversalSpeed;
		}
	}
	else
	{
		for (int i = 0; i < spawnAmount; i++)
		{
			FVector currentPos = this->GetActorLocation();

			float currentSpawnPosOffset = FMath::RandRange(MinMaxSpawnPosOffset.X, MinMaxSpawnPosOffset.Y);

			AObstacleActor* currentObstacle = GetWorld()->SpawnActor<AObstacleActor>(
				ObstacleToSpawn, currentPos + FVector(currentSpawnPosOffset, 0, 0), this->GetActorRotation());
			currentObstacle->OnObstacleReachEnd.AddDynamic(this, &AObstacleSpawner::DeleteObstacle);

			ObstacleDict.Add(currentObstacle->GetUniqueID(), currentObstacle);

			currentObstacle->SetActorLocation(currentPos + FVector(currentSpawnPosOffset, 0, 0));

			currentObstacle->MovementDir = UniversalMovementDir;
			currentObstacle->Speed = UniversalSpeed;
		}
	}

	UniversalSpeed += 1;

	CurrentSpawnDelay = FMath::RandRange(MinMaxSpawnDelay.X, MinMaxSpawnDelay.Y);
}

void AObstacleSpawner::SpawnFloor()
{
	FVector currentPos = this->GetActorLocation();

	AObstacleActor* currentFloor = GetWorld()->SpawnActor<AObstacleActor>(
		FloorReference, currentPos - FVector(0, 0, 170), this->GetActorRotation());
	currentFloor->OnObstacleReachEnd.AddDynamic(this, &AObstacleSpawner::DeleteFloor);

	currentFloor->MovementDir = UniversalMovementDir;
	currentFloor->Speed = UniversalSpeed;

	FloorDict.Add(currentFloor->GetUniqueID(), currentFloor);
}

void AObstacleSpawner::ReturnObstacleToQueue(float ObstacleId)
{
	ObstacleDict[ObstacleId]->OnObstacleReachEnd.Remove(this, "ReturnObstacleToQueue");
	ObstaclePool->Enqueue(ObstacleDict[ObstacleId]);
	ObstacleDict.Remove(ObstacleId);
}

void AObstacleSpawner::DeleteObstacle(float ObstacleId)
{
	ObstacleDict[ObstacleId]->Destroy();
	ObstacleDict.Remove(ObstacleId);
}

void AObstacleSpawner::DeleteFloor(float ObstacleId)
{
	FloorDict[ObstacleId]->Destroy();
	FloorDict.Remove(ObstacleId);
}


// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObstacleSpawner::SetHighScores()
{
	USaveGameHighscore* SaveGameInstance = Cast<USaveGameHighscore>(
		UGameplayStatics::CreateSaveGameObject(USaveGameHighscore::StaticClass()));

	if (HighScores.Num() == 5)
	{
		if (HighScores[HighScores.Num() - 1] < Points)
		{
			HighScores.RemoveAt(HighScores.Num() - 1);
		}
	}

	HighScores.Add(Points);
	HighScores.Sort([](const int Num1, const int Num2)
	{
		return Num1 > Num2;
	});
	SaveGameInstance->HighScores = HighScores;

	SaveGameInstance->HighScores.Shrink();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("HighScoreSlot"), 0);

	UE_LOG(LogTemp, Warning, TEXT("Saved Game, High score is: %d"), SaveGameInstance->HighScores[0]);

	FName LevelName = TEXT("MainMenuLevel");

	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

void AObstacleSpawner::LoadHighScores()
{
	USaveGameHighscore* SaveGameInstance = Cast<USaveGameHighscore>(UGameplayStatics::LoadGameFromSlot("HighScoreSlot", 0));

	HighScores = SaveGameInstance->HighScores;

	UE_LOG(LogTemp, Warning, TEXT("Loaded Game, High score is: %d"), HighScores[0]);
}
