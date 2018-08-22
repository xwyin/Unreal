// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MySatCoord.generated.h"

class UMyLoadConfig;

USTRUCT(BlueprintType)
struct FArrayWrapper
{
	GENERATED_BODY()

	FArrayWrapper() {}

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVector> Coordinates;

	FArrayWrapper(const TArray<FVector> &coords) {
		Coordinates = coords;
	}
};

UCLASS(Blueprintable)
class MYPROJECT_API UMySatCoord : public UObject
{
	GENERATED_BODY()

public:

	TMap<FString, TArray<FVector>> satDatabase; //final map where information of all satellites are stored
	TArray<FString> fileNames;
	
	UFUNCTION(BlueprintCallable)
		TArray<FVector> GetSpecificSatInfo(FString satname);

	UFUNCTION(BlueprintCallable)
		void ReadAllFiles();

	UFUNCTION(BlueprintCallable)
		TMap<FString, FArrayWrapper> GetAllSatInfo();

protected:

	UFUNCTION(BlueprintCallable)
		void SaveSatInfo(FString path);

	void ParseCoord(TArray<FVector> &inputCoord, FString lineI);
	float StrToFloat(FString sciNum);
	float ProcessCoord(float ephemeris);
};
