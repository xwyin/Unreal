// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/TimerManager.h"
#include "MyGameInstance.h" 
#include "MySun.generated.h"

UCLASS()
class MYPROJECT_API AMySun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UpdateSunLocation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float angle = 0.0f;
	float timerRate;
	FVector rotate;
	FVector newLocation;
	FTimerHandle timerHandle;

};
