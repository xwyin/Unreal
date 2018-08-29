// Fill out your copyright notice in the Description page of Project Settings.

#include "MySatellites.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"
#include "CoreMinimal.h"

// Sets default values
AMySatellites::AMySatellites()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void AMySatellites::BeginPlay()
{
	Super::BeginPlay();

	satMeshComponent->SetStaticMesh(satMesh);

	UMyGameInstance* instance = Cast<UMyGameInstance>(GetGameInstance());

	if (instance) {
		//UE_LOG(LogTemp, Warning, TEXT("Getting info from SatDatabase"));
		//UE_LOG(LogTemp, Warning, TEXT("satName: %s"), *satName);
		satInfo = instance->GetSatDatabase()->GetSpecificSatInfo(satName);
		timerRate = instance->GetSpeedModifier();
		//centralObject = instance->GetCentralObject();
	}
	//UE_LOG(LogTemp, Warning, TEXT("Setting Up Timer"));
	GetWorldTimerManager().SetTimer(timerHandle, this, &AMySatellites::UpdateSatLocation, timerRate, true, 0.0f);

	//UE_LOG(LogTemp, Warning, TEXT("Actor Location: %s"), *GetActorLocation().ToString());
	//FVector facingDir = centralObject->GetActorLocation() - GetActorLocation();
	FVector facingDir = centerEarth - GetActorLocation();
	SetActorRotation(facingDir.ToOrientationQuat());
}

// Called every frame
void AMySatellites::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	alpha = GetWorldTimerManager().GetTimerElapsed(timerHandle) / timerRate;
	newLocation = FMath::Lerp(satInfo[i], satInfo[i + 1], alpha);

	FVector prevDir = GetActorLocation() - centerEarth;
	FVector newDir = newLocation - centerEarth;

	prevDir.Normalize();
	newDir.Normalize();

	FQuat quat = FQuat::FindBetweenVectors(prevDir, newDir);
	AddActorWorldRotation(quat);
	SetActorLocation(newLocation);
}

void AMySatellites::UpdateSatLocation() {
	if (i == satInfo.Num() - 2) {
		GetWorldTimerManager().ClearTimer(timerHandle);
		i = 0;
		//to be implemented, throw warning at user end of coordinates data, prompt for restart or exit
	}
	else {
		i++;
	}
}

