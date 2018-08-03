// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MySatCoord.generated.h"

UCLASS(Blueprintable,BlueprintType)
class MYPROJECT_API UMySatCoord : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
		TArray<FVector> SaveSatInfo(FString path);
		void ReadAllFiles();

protected:

	UFUNCTION(BlueprintCallable)

		
		void ParseCoord(TArray<FVector> &inputCoord, FString lineI);
		float StrToFloat(FString sciNum);
		float ProcessCoord(float preProcess);

};
