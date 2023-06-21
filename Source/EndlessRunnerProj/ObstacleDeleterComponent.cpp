// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleDeleterComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UObstacleDeleterComponent::UObstacleDeleterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObstacleDeleterComponent::BeginPlay()
{
	Super::BeginPlay();
}



void UObstacleDeleterComponent::GetObstacle()
{

	bool bShouldDeleteObstacle = UKismetMathLibrary::RandomIntegerInRange(1,100) < 30;
	
	if(!bShouldDeleteObstacle)
	{
		return;
	}
	
	FVector CastDir = FVector(0,-1, 0);
	
	FVector TraceStart = GetOwner()->GetActorLocation();
	FVector TraceEnd = TraceStart + CastDir * ObstacleDistanceCheck;

	TraceStart.X = 0;
	
	TArray<FHitResult> HitResults;

	ETraceTypeQuery CollisionChannel = ETraceTypeQuery();
	
	FVector BoxTraceSize = FVector(1000,0,0);
	
	UKismetSystemLibrary::BoxTraceMulti(GetWorld(), TraceStart, TraceEnd, BoxTraceSize, FRotator::ZeroRotator, CollisionChannel, false, IgnoredActors, EDrawDebugTrace::None,HitResults, true);

	for (int i = 0; i < HitResults.Num(); i++)
	{

		FString ActorName = HitResults[i].GetActor()->GetName();
		
		UE_LOG(LogTemp, Warning, TEXT("Actor name: %s"), *ActorName);
		
		TArray<USceneComponent*> ActorsComponents;

		HitResults[i].GetActor()->GetRootComponent()->GetChildrenComponents(true, ActorsComponents);

		UE_LOG(LogTemp, Warning, TEXT("Actor children amount: %d"), ActorsComponents.Num());

		
		for(int j = 0; j < ActorsComponents.Num(); j++)
		{
			FString ComponentName = ActorsComponents[j]->GetName();
		
			UE_LOG(LogTemp, Warning, TEXT("Component name: %s"), *ComponentName);

			USceneComponent* CurrentComponent = ActorsComponents[j];
			
			if(CurrentComponent->ComponentHasTag("Obstacle") && CurrentComponent->GetComponentLocation().Y < TraceStart.Y + 1000)
			{
				UE_LOG(LogTemp, Warning, TEXT("Deleted object"))
				ActorsComponents[j]->DestroyComponent();
				return;
			}
		}
	}
}


// Called every frame
void UObstacleDeleterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

