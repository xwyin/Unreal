// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyLoadConfig.generated.h"

/**
 * This class loads the .sa files path from config file
 */

UCLASS(config=SaPath,Blueprintable, BlueprintType)
class MYPROJECT_API UMyLoadConfig : public UObject
{
	GENERATED_BODY()

public:
		
		UMyLoadConfig();

		UPROPERTY(Config)
			FString path; //path to read SA files from

		UFUNCTION()
			FString GetSaPath();
};

