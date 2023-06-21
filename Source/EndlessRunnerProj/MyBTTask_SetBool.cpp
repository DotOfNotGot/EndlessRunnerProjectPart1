// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_SetBool.h"

#include "BehaviorTree/BlackboardComponent.h"

void UMyBTTask_SetBool::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UMyBTTask_SetBool::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

EBTNodeResult::Type UMyBTTask_SetBool::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BoolName, bNewValue);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
