// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
/**
 * 
 */
template<typename T>
class ENDLESSRUNNERPROJ_API ActorPooler
{
	static_assert(std::is_base_of<AActor, T>::value, "PoolObject must be derived from AActor");

	UWorld* World;
	TSubclassOf<T> PoolObject;
	TQueue<TObjectPtr<T>> Pool;
	bool bInitialized;
protected:
	void Create();
public:
	TObjectPtr<T> Pop();
	void Enqueue(TObjectPtr<T> object);
	void Populate(int amount);
	ActorPooler(UWorld* world, TSubclassOf<T> poolObject);
	~ActorPooler();
};
template<typename T>
void ActorPooler<T>::Create()
{
	if (!bInitialized) { return; }
	T* ptr = World->SpawnActor<T>(PoolObject, FVector(0, 0, 0), FRotator(0, 0, 0));
	ptr->SetActorHiddenInGame(true);
	ptr->SetActorTickEnabled(false);
	Pool.Enqueue(ptr);
}

template<typename T>
TObjectPtr<T> ActorPooler<T>::Pop()
{
	if (!bInitialized) { return nullptr; }
	if (Pool.IsEmpty())
	{
		Create();
	}
	TObjectPtr<T> obj;
	Pool.Dequeue(obj);
	obj->SetActorHiddenInGame(false);
	obj->SetActorTickEnabled(true);
	obj->SetActorEnableCollision(true);
	return obj;
}

template<typename T>
void ActorPooler<T>::Enqueue(TObjectPtr<T> object)
{
	if (!bInitialized) { return; }
	object->SetActorHiddenInGame(true);
	object->SetActorTickEnabled(false);
	object->SetActorEnableCollision(false);
	Pool.Enqueue(object);
}

template<typename T>
void ActorPooler<T>::Populate(int amount)
{
	if (!bInitialized) { return; }
	for (int i = 0; i < amount; i++)
	{
		Create();
	}
}

template<typename T>
ActorPooler<T>::ActorPooler(UWorld* world, TSubclassOf<T> poolObject)
{
	if (!world->IsValidLowLevel() || !IsValid(poolObject))
	{
		bInitialized = false;
		return;
	}

	World = world;
	PoolObject = poolObject;
	bInitialized = true;
}

template<typename T>
ActorPooler<T>::~ActorPooler()
{
	World = NULL;
}