// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlanets.h"
#include "Engine/EngineTypes.h"
#include "CoreMinimal.h"

// Sets default values
AMyPlanets::AMyPlanets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void AMyPlanets::BeginPlay()
{
	Super::BeginPlay();
	int8 timerCalled = 0;
	UMyGameInstance* instance = Cast<UMyGameInstance>(GetGameInstance());
	if (instance){
		UE_LOG(LogTemp, Warning, TEXT("Not null"));
		satDatabase = instance->GetSatDatabase()->LoadCoord("C:\\Users\\xyin\\Desktop\\testInput.sa");
	}
	GetWorldTimerManager().SetTimer(timerHandle, this, &AMyPlanets::UpdateSatLocation, timerRate, true, 0.0f);
}

// Called every frame
void AMyPlanets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	alpha = GetWorldTimerManager().GetTimerElapsed(timerHandle) / timerRate;
	newLocation = FMath::Lerp(satDatabase[i], satDatabase[i + 1], alpha);
	SetActorLocation(newLocation);
}

void AMyPlanets::UpdateSatLocation() {
	
	if (i == satDatabase.Num() - 1) {
		GetWorldTimerManager().ClearTimer(timerHandle);
		i = 0;
	}
	else {
		i++;
	}
}