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
		TArray<FVector> LoadCoord(FString path);

protected:

	UFUNCTION(BlueprintCallable)
		
		void InputCoord(TArray<FVector> &inputCoord, FString lineI);
		float StrToFloat(FString sciNum);
		float ProcessCoord(float preProcess);

};
