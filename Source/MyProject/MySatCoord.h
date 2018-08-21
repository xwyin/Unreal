// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MySatCoord.generated.h"

class UMyLoadConfig;

UCLASS(Blueprintable,BlueprintType)
class MYPROJECT_API UMySatCoord : public UObject
{
	GENERATED_BODY()

public:

	TMap<FString, TArray<FVector>> satDatabase; //final map where information of all satellites are stored
	TArray<FString> fileNames;

	UFUNCTION(BlueprintCallable)
		void ReadAllFiles();
		TArray<FVector> GetSpecificSatInfo(FString satname);

protected:

	UFUNCTION(BlueprintCallable)
		void SaveSatInfo(FString path);
		void ParseCoord(TArray<FVector> &inputCoord, FString lineI);
		float StrToFloat(FString sciNum);
		float ProcessCoord(float ephemeris);
};
