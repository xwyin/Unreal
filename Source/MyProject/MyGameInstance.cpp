// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "MySatCoord.h"
#include "Engine.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
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

void UMyGameInstance::FindCentralObject() {
	UE_LOG(LogTemp, Warning, TEXT("Calling FindCentralObject()"));

	UWorld* wp = GEngine->GetWorld();
	checkf(wp, TEXT("World Does not exist"));

	for (TActorIterator<AActor> ActorItr(wp); ActorItr; ++ActorItr) {
		AActor *Mesh = *ActorItr;
		UE_LOG(LogTemp, Warning, TEXT("ActorName %s"), *ActorItr->GetName());
		if (ActorItr->GetName() == FString("Earth")) {
			UE_LOG(LogTemp, Warning, TEXT("Central Object Found"));
			centralObject = Mesh;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Finished Searching for Central Object"));
}

AActor* UMyGameInstance::GetCentralObject() {
	return centralObject;
}

