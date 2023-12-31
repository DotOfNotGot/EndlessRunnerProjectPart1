// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_CheckForObstacle.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERPROJ_API UMyBTTask_CheckForObstacle : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	UPROPERTY(EditAnywhere)
	float ObstacleDistanceCheck = 1000.0f;
	
	UPROPERTY(EditAnywhere)
	float SafeDistanceCheck = 1000.0f;
	
	UPROPERTY(EditAnywhere)
	TArray<FVector> PossiblePositions;

public:


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
