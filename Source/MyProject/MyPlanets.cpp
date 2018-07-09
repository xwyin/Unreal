// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlanets.h"
#include "CoreMinimal.h"

// Sets default values
AMyPlanets::AMyPlanets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMyPlanets::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Hiiiii"));
	Super::BeginPlay();
	UMyGameInstance* instance = Cast<UMyGameInstance>(GetGameInstance());
	if (instance){
		UE_LOG(LogTemp, Warning, TEXT("Not null"));
		instance->GetSatDatbase();
	}

}

// Called every frame
void AMyPlanets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}