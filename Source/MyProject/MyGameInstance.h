// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS(Blueprintable)
class MYPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
		UPROPERTY(BlueprintReadOnly)
			class UMySatCoord* satDatabase;
		
public:
		UMyGameInstance();
		float speedModifier = 0.05f; //default 60.0f for real time updates, scales down to fastforward

		UFUNCTION(BlueprintCallable)
			class UMySatCoord* GetSatDatabase();
			float GetSpeedModifier();
			float SetSpeedModifier(float userInputModifier);
};

