// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameInstance.h"
#include "MySatCoord.h"
#include "Public/TimerManager.h"
#include "GameFramework/Actor.h"
#include "MySatellites.generated.h"

UCLASS()
class MYPROJECT_API AMySatellites : public AActor
{
	GENERATED_BODY()
	
public:	
	AMySatellites();
	float timerRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satellite | Center")
	AActor* centralObject;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<FVector> satDatabase;
	int32 i = 0; 
	float alpha;
	FVector newLocation;
	FTimerHandle timerHandle;

	void UpdateSatLocation();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
