// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCheckObject, float, ActorId);
UCLASS()

class ENDLESSRUNNERPROJ_API ATile : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable)
	void BroadcastObstacleReachEnd();	

protected:

public:	

	FCheckObject OnObstacleReachEnd;
};

