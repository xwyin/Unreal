// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "MySatCoord.h"
#include "MyLoadConfig.h"


//Default Constructor for game instance --> Creates a UMySatCoord Object
UMyGameInstance::UMyGameInstance() {
	satDatabase = NewObject<UMySatCoord>();
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

