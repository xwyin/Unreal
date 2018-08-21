// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpawner.h"


// Sets default values
AMySpawner::AMySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

