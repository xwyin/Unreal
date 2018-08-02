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
		timerRate = instance->GetTimerRate();
	}
}

// Called every frame
void AMySun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector radius = FVector(0, 2550, 0);
	newLocation = FVector(0, 0, 0);

	angle += 360.0f / 86400.0f * (60.0f / timerRate);
	if (angle >= 360.f) {
		angle = 0;
	}

	rotate = radius.RotateAngleAxis(angle, FVector(0, 0, 1));

	newLocation.X += rotate.X;
	newLocation.Y += rotate.Y;
	newLocation.Z += rotate.Z;

	SetActorLocation(newLocation);
}
