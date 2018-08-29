// Fill out your copyright notice in the Description page of Project Settings.

#include "MySun.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMySun::AMySun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMySun::BeginPlay()
{
	Super::BeginPlay();
	UMyGameInstance* instance = Cast<UMyGameInstance>(GetGameInstance());
	if (instance) {
		speedModifier = instance->GetSpeedModifier();
		startTime = instance->GetSatDatabase()->GetStartTime();
	}
	
}

// Called every frame
/**
* Equation for angle: One revolution of Earth is one day (86400s) and 360 degrees
* Timer for trigger update satellite location is triggered at 60s interval for regular speed
* TimerRate is used as a multiplier to control the speed of the scene/components
*/
void AMySun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	radius = FVector(800, 0, 0);

	//angle += 360.0f / 86400.0f * (60.0f / speedModifier);
	angle += 0.25 / speedModifier;

	if (angle >= 360.f) {
		angle = 0;
	}

	rotate = radius.RotateAngleAxis(angle, FVector(0, 0, 1));

	FVector newLocation = FindStartLocation();

	newLocation.X += rotate.X;
	newLocation.Y += rotate.Y;
	newLocation.Z += rotate.Z;

	SetActorLocation(newLocation);
}

//This function determines the location of the sun based on the start time parsed from .sa file
FVector AMySun::FindStartLocation() {
	float timeInSeconds = startTime.GetHour() * 3600.f + startTime.GetMinute() * 60.f + startTime.GetSecond() * 1.f;
	//float startAngle = (timeInSeconds * 360 / 86400 + 180) % 360;
	float startAngle =  FMath::Fmod((timeInSeconds * 0.0041667 + 180.0) , 360);
	float posX = radius.X * FMath::Sin(startAngle); 
	float posY = radius.X * FMath::Cos(startAngle);

	FVector startLocation;

	startLocation.X = posX;
	startLocation.Y = posY;
	startLocation.Z = 0;

	return startLocation;
}
