// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "MySatCoord.h"
#include "MyLoadConfig.h"


//Default Constructor for game instance --> Creates a UMySatCoord Object
UMyGameInstance::UMyGameInstance() {
	UE_LOG(LogTemp, Warning, TEXT("Construct UMySatCoord Object from MyGameInstance"));
	satDatabase = NewObject<UMySatCoord>();
	satDatabase->ReadAllFiles();
}

UMySatCoord* UMyGameInstance::GetSatDatabase() {
	return satDatabase;
}

float UMyGameInstance::GetSpeedModifier() {
	return speedModifier;
}

float UMyGameInstance::SetSpeedModifier(float timerRateInput) {
	return speedModifier = timerRateInput;
}

