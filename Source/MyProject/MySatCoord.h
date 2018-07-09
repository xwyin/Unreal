// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MySatCoord.generated.h"

/**
 * This struct defines information of satellites in Ephemeris format
 */
USTRUCT(BlueprintType)
struct FSatInfo
{
	GENERATED_BODY()

		UPROPERTY()
			TMap<uint32,FVector> satInfo; //time and coordinate

			//Just a function to print the map to check if map was constructed properly
			void PrintSat(){
				UE_LOG(LogTemp, Warning, TEXT("Called Print"));
				for (auto It = satInfo.CreateConstIterator(); It; ++It)
				{
					UE_LOG(LogTemp, Warning, TEXT("InsidePrint"));
					UE_LOG(LogTemp, Warning, TEXT("Time: %f"), It.Key()); 
					UE_LOG(LogTemp, Warning, TEXT("Position X: %f"), It.Value().X); 
					UE_LOG(LogTemp, Warning, TEXT("Position Y: %f"), It.Value().Y);
					UE_LOG(LogTemp, Warning, TEXT("Position Z: %f"), It.Value().Z);
				}
			}
};

UCLASS(Blueprintable,BlueprintType)
class MYPROJECT_API UMySatCoord : public UObject
{
	GENERATED_BODY()

protected:

	//TMap<FString,FSatInfo> SatCoord;
	/** This Map stores the information of satellites in Ephemeris format */
	
	UFUNCTION(BlueprintCallable)
		void LoadCoord(FString path);
		void InputCoord(FSatInfo inputCoord, FString lineI);
		float StrToFloat(FString sciNum);
		float ProcessCoord(float preProcess);

};
