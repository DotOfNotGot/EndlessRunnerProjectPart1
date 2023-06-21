// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_CheckForObstacle.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

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

	FVector TraceStart = RunnerAiCharacter->GetActorLocation();
	FVector TraceEnd = TraceStart + RunnerAiCharacter->GetActorForwardVector() * 2000;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(RunnerAiCharacter);

	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);

	DrawDebugLine(GetWorld(), TraceStart, Hit.Location, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);

	FVector NewTestLocation = TraceStart - RunnerAiCharacter->GetActorRightVector() * 300;

	
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("AvoidObstacle", NewTestLocation);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("ShouldMove", Hit.bBlockingHit);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
