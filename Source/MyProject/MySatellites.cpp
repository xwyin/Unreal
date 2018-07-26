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
		satDatabase = instance->GetSatDatabase()->SaveSatInfo("C:\\Users\\xyin\\Desktop\\testInput.sa");
	}
	GetWorldTimerManager().SetTimer(timerHandle, this, &AMySatellites::UpdateSatLocation, timerRate, true, 0.0f);
	
	
}

// Called every frame
void AMySatellites::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	alpha = GetWorldTimerManager().GetTimerElapsed(timerHandle) / timerRate;
	newLocation = FMath::Lerp(satDatabase[i], satDatabase[i + 1], alpha);
	SetActorLocation(newLocation);
	FRotator lookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), centerEarth);
	//FQuat testRot = FRotator(lookAtRot.Pitch, lookAtRot.Yaw, GetActorRotation().Roll).Quaternion();
	
	//FRotator satRot = FRotator(lookAtRot.Pitch, lookAtRot.Yaw, GetActorRotation().Roll);
	FQuat delta = (lookAtRot - GetActorRotation()).Quaternion();
	//FQuat testRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), centerEarth).Quaternion();
	GetComponents<UStaticMeshComponent>(satMeshs);
	UStaticMeshComponent* child = satMeshs[0];
	FTransform  transform = this->GetTransform();
	transform.ConcatenateRotation(delta);
	//child->SetRelativeRotation(testRot);
	SetActorTransform(transform);
	//SetActorRotation(testRot);
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