// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MySatCoord.generated.h"

/**
 * This struct defines information of satellites in Ephemeris format
 */
USTRUCT(BlueprintType)
struct FSatInfoEphemeris
{
	GENERATED_BODY()

		UPROPERTY()
		float eTime;
		float ePosX;
		float ePosY;
		float ePosZ;
};

/**
* This struct defines information of satellites after conversion to UTC and 3DVector in XYZ axis 
*/
USTRUCT(BlueprintType)
struct FSatInfo
{
	GENERATED_BODY()

		UPROPERTY()
		float satTime;
		float satPosX;
		float satPosY;
		float satPosZ;
};

UCLASS(Blueprintable,BlueprintType)
class MYPROJECT_API UMySatCoord : public UObject
{
	GENERATED_BODY()

protected:

	TMap<FString,FSatInfo> SatCoord;
	/** This Map stores the information of satellites in Ephemeris format */
	
	UFUNCTION(BlueprintCallable)
		TArray<FSatInfoEphemeris> LoadCoord(FString path);

};
