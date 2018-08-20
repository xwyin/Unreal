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
	UMyGameInstance* instance = Cast<UMyGameInstance>(GetGameInstance());

	if (instance){
		UE_LOG(LogTemp, Warning, TEXT("Getting info from SatDatabase"));
		satDatabase = instance->GetSatDatabase()->GetSpecificSatInfo(GetName());
		timerRate = instance->GetSpeedModifier();
	}

	GetWorldTimerManager().SetTimer(timerHandle, this, &AMySatellites::UpdateSatLocation, timerRate, true, 0.0f);
	FVector facingDir = centralObject->GetActorLocation() - GetActorLocation();
	SetActorRotation(facingDir.ToOrientationQuat());
}

// Called every frame
void AMySatellites::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	alpha = GetWorldTimerManager().GetTimerElapsed(timerHandle) / timerRate;
	newLocation = FMath::Lerp(satDatabase[i], satDatabase[i + 1], alpha);

	FVector prevDir = GetActorLocation() - centralObject->GetActorLocation();
	FVector newDir = newLocation - centralObject->GetActorLocation();

	prevDir.Normalize();
	newDir.Normalize();

	FQuat quat = FQuat::FindBetweenVectors(prevDir, newDir);
	AddActorWorldRotation(quat);
	SetActorLocation(newLocation);
}

void AMySatellites::UpdateSatLocation() {
	if (i == satDatabase.Num() - 2) {
		GetWorldTimerManager().ClearTimer(timerHandle);
		i = 0;
		//to be implemented, throw warning at user end of coordinates data, prompt for restart or exit
	}
	else {
		i++;
	}
}