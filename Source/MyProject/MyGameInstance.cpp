// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "MySatCoord.h"

UMyGameInstance::UMyGameInstance() {
	UE_LOG(LogTemp, Warning, TEXT("Gameinstance constructor"));
	satDatabase = NewObject<UMySatCoord>();
}

UMySatCoord* UMyGameInstance::GetSatDatabase() {
	UE_LOG(LogTemp, Warning, TEXT("Gameinstance return db"));
	return satDatabase;
}

