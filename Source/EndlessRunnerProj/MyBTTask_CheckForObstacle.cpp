// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_CheckForObstacle.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UMyBTTask_CheckForObstacle::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UMyBTTask_CheckForObstacle::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

EBTNodeResult::Type UMyBTTask_CheckForObstacle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const Controller = OwnerComp.GetAIOwner();

	ACharacter* RunnerAiCharacter = Controller->GetCharacter();

	FVector CastDir = FVector(0,-1, 0);
	
	FVector TraceStart = RunnerAiCharacter->GetActorLocation();
	FVector TraceEnd = TraceStart + CastDir * ObstacleDistanceCheck;

	TArray<AActor*> IgnoredActors;

	IgnoredActors.Add(RunnerAiCharacter);
	IgnoredActors.Add(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	FHitResult Hit;

	ETraceTypeQuery CollisionChannel = ETraceTypeQuery();

	FVector BoxTraceSize = FVector(100,0,0);
	
	UKismetSystemLibrary::BoxTraceSingle(GetWorld(), TraceStart, TraceEnd, BoxTraceSize, FRotator::ZeroRotator, CollisionChannel, false, IgnoredActors, EDrawDebugTrace::None,Hit, true);

	
	FVector NewSafePos;

	if(Hit.bBlockingHit)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("ShouldMove", true);

		TArray<FVector> SafePositions;

		SafePositions.Append(PossiblePositions);
		
		for (int i = SafePositions.Num() - 1; i >= 0; i--)
		{

			FVector HitPosYAdjusted = SafePositions[i];

			FHitResult SafePosCheckHit;

			if(SafePosCheckHit.bBlockingHit)
			{
				HitPosYAdjusted.Y = SafePosCheckHit.Location.Y;
			}
			else
			{
				HitPosYAdjusted.Y = Hit.Location.Y;
			}
			
			FVector SafePosCheckStart = HitPosYAdjusted;
			FVector SafePosCheckEnd = HitPosYAdjusted + CastDir * SafeDistanceCheck;
			
			FVector SafeCheckBoxTraceSize = FVector(100,0,0);
			
			UKismetSystemLibrary::BoxTraceSingle(GetWorld(), SafePosCheckStart, SafePosCheckEnd, SafeCheckBoxTraceSize, FRotator::ZeroRotator, CollisionChannel, false, IgnoredActors, EDrawDebugTrace::None,SafePosCheckHit, true);
			
			if(SafePosCheckHit.bBlockingHit)
			{
				SafePositions.RemoveAt(i);
			}
		}

		SafePositions.Sort([TraceStart] (FVector A, FVector B)
		{
			return FVector::DistSquared(TraceStart, A) < FVector::DistSquared(TraceStart, B);
		});

		if(SafePositions.Num() > 0)
		{
			NewSafePos = SafePositions[0];
		}
		else
		{
			NewSafePos = TraceStart;
		}
		
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("AvoidObstacle", NewSafePos);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("ForwardDirection", NewSafePos + CastDir);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("ShouldMove", false);
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
