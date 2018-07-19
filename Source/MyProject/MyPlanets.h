// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameInstance.h"
#include "MySatCoord.h"
#include "Public/TimerManager.h"
#include "GameFramework/Actor.h"
#include "MyPlanets.generated.h"

UCLASS()
class MYPROJECT_API AMyPlanets : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPlanets();
	float timerRate = 1.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	TArray<FVector> satDatabase;
	float i = 0.0f; 
	float alpha;
	FVector newLocation;
	FTimerHandle timerHandle;
	void UpdateSatLocation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
