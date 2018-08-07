// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class MYPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
		UPROPERTY()
		class UMySatCoord* satDatabase;

public:
		UMyGameInstance();
		class UMySatCoord* GetSatDatabase();
		float speedModifier = 0.05f; //default 60.0f for real time updates, scales down to fastforward
		float GetSpeedModifier();
		float SetSpeedModifier(float userInputModifier);
};

