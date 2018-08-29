// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MySatCoord.h"
#include "MyGameInstance.h"
#include "Public/TimerManager.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "MySatellites.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API AMySatellites : public AActor
{
	GENERATED_BODY()
	
public:	
	AMySatellites();
	float timerRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satellite | Name", Meta = (ExposeOnSpawn=true))
		FString satName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satellite | Mesh", Meta = (ExposeOnSpawn = true))
		UStaticMesh* satMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satellite | Center")
		AActor* centralObject;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<FVector> satInfo;
	int32 i = 0; 
	float alpha;
	FVector newLocation;
	FVector centerEarth = FVector(0.0, 0.0, 0.0);
	FTimerHandle timerHandle;
	UStaticMeshComponent* satMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	void UpdateSatLocation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
