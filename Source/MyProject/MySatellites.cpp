// Fill out your copyright notice in the Description page of Project Settings.

#include "MySatellites.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
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
	int8 timerCalled = 0;
	UMyGameInstance* instance = Cast<UMyGameInstance>(GetGameInstance());
	if (instance){
		instance->GetSatDatabase()->ReadAllFiles();
		//satDatabase = instance->GetSatDatabase()->GetSpecificSatInfo(GetName());
		timerRate = instance->GetTimerRate();
	}
	GetWorldTimerManager().SetTimer(timerHandle, this, &AMySatellites::UpdateSatLocation, timerRate, true, 0.0f);
	
	rotationAxis = FVector::CrossProduct(GetActorForwardVector(), satDatabase[0] - GetActorLocation());
	rotationAxis.Normalize();
	
}

// Called every frame
void AMySatellites::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	alpha = GetWorldTimerManager().GetTimerElapsed(timerHandle) / timerRate;
	newLocation = FMath::Lerp(satDatabase[i], satDatabase[i + 1], alpha);

	FVector prevDir = centerEarth - GetActorLocation();
	FVector newDir = centerEarth - newLocation;

	FRotator preRot = centerEarth.Rotation() - GetActorRotation();
	FRotator newRot = centerEarth.Rotation() - newLocation.Rotation();

	preRot.Normalize();
	newRot.Normalize();

	prevDir.Normalize();
	newDir.Normalize();

	float angle = FMath::Acos((FVector::DotProduct(prevDir, newDir)));
	FQuat quat(rotationAxis, angle);
	AddActorLocalRotation(quat);
	SetActorLocation(newLocation);
}

void AMySatellites::UpdateSatLocation() {
	
	if (i == satDatabase.Num() - 2) {
		GetWorldTimerManager().ClearTimer(timerHandle);
		i = 0;
	}
	else {
		i++;
	}
}