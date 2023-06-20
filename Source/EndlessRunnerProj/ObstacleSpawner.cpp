// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"

#include "HealthComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void AObstacleSpawner::MoveTiles(float DeltaTime)
{
	for (int i = 0; i < CurrentTiles.Num(); i++)
	{
		ATile* CurrentTile = CurrentTiles[i];

		if(CurrentTile == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Tile nullptr"));
			continue;
		}
		
		CurrentTile->GetRootComponent()->SetRelativeLocation(CurrentTile->GetActorLocation() + GetActorRightVector() * Speed * DeltaTime);
	}

	DistanceTraveled += Speed * DeltaTime;
	
	Points = (int)(DistanceTraveled / 100);
	FOnScoreIncreased.Broadcast(Points);

	if (DistanceTraveled / TileLength > AmountOfTilesCleared)
	{
		SpawnObstacle();
		if (AmountOfTilesCleared % TilesClearedForSpeedUp == 0)
		{
			Speed *= 1.5f;
			TilesClearedForSpeedUp *= 2;
		}
		
		AmountOfTilesCleared++;
	}
	
}

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

	if(StartTile != nullptr)
	{
		CurrentTiles.Add(StartTile);
		ObstacleDict.Add(StartTile->GetUniqueID(), StartTile);
		StartTile->OnObstacleReachEnd.AddDynamic(this, &AObstacleSpawner::DeleteTile);
	}
	
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	UHealthComponent* PlayerHealthComponent = Cast<UHealthComponent>(
		PlayerCharacter->GetComponentByClass(UHealthComponent::StaticClass()));

	if (PlayerHealthComponent != nullptr)
	{
		PlayerHealthComponent->FOnDeath.AddDynamic(this, &AObstacleSpawner::SetHighScores);
	}

	Super::BeginPlay();
}

TSubclassOf<ATile> AObstacleSpawner::GetRandomTileToSpawn()
{
	int RandomIndex = FMath::RandRange(0, TilesToPick.Num() - 1);

	return TilesToPick[RandomIndex];
}

void AObstacleSpawner::SpawnObstacle()
{
	FVector currentPos = this->GetActorLocation();

	const float SpawnDistanceCorrection = AmountOfTilesCleared * TileLength - DistanceTraveled;
	
	ATile* CurrentObstacle = GetWorld()->SpawnActor<ATile>(
		GetRandomTileToSpawn(), currentPos + (TileLength + SpawnDistanceCorrection) * -GetActorRightVector(), this->GetActorRotation());
	
	CurrentObstacle->OnObstacleReachEnd.AddDynamic(this, &AObstacleSpawner::DeleteTile);

	CurrentTiles.Add(CurrentObstacle);

	ObstacleDict.Add(CurrentObstacle->GetUniqueID(), CurrentObstacle);
}

void AObstacleSpawner::DeleteTile(float ObstacleId)
{
	ObstacleDict[ObstacleId]->OnObstacleReachEnd.Remove(this, "DeleteTile");

	CurrentTiles.Remove(ObstacleDict[ObstacleId]);
	CurrentTiles.Shrink();
	
	ObstacleDict[ObstacleId]->Destroy();
	ObstacleDict.Remove(ObstacleId);
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	MoveTiles(DeltaTime);
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
	USaveGameHighscore* SaveGameInstance = Cast<USaveGameHighscore>(
		UGameplayStatics::LoadGameFromSlot("HighScoreSlot", 0));

	if(SaveGameInstance != nullptr)
	{
		HighScores = SaveGameInstance->HighScores;

		UE_LOG(LogTemp, Warning, TEXT("Loaded Game, High score is: %d"), HighScores[0]);
	}

}
