// Fill out your copyright notice in the Description page of Project Settings.

#include "MySatCoord.h"
#include "Misc/FileHelper.h"
#include "GenericPlatform/GenericPlatform.h"
#include "HAL/PlatformFilemanager.h"
#include "Containers/UnrealString.h"
#include <sstream>	
#include <string>


IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

//This function reads the .sa file and return info as a map
void UMySatCoord::LoadCoord(FString path) {
	TArray<FString> arr;
	if (PlatformFile.FileExists(*path)) {
		FFileHelper::LoadFileToStringArray(arr, *path);
	}

	bool startParse = false;
	FString satName = "NEOSSAT";
	FSatInfo inputCoord; 
	TMap<FString, FSatInfo> satDatabase; //final map where information of all satellites are stored

	for (int32 i = 0; i < arr.Num(); i++) {
		if (arr[i] == "BEGIN Satellite") {
			//to be implemented, parse name
		}

		if (arr[i] == "EphemerisTimePosVel") {
			startParse = true;
		}

		if (arr[i] == "END Ephemeris") {
			break;
		}

		if (startParse && !arr[i].IsEmpty()) {
			InputCoord(inputCoord,arr[i]);
		}
	}
	satDatabase.Add(satName, inputCoord);
	UE_LOG(LogTemp, Warning, TEXT("This many sat: %d"), satDatabase.Num());
	satDatabase.Find(satName)->PrintSat();
}

//This function parses time and position information of satellite
void UMySatCoord::InputCoord(FSatInfo &inputCoord, FString lineI) {
	int8 arrayIndex = 0;
	FString tempString;
	float tempFloat;
	FVector satPosition;
	float satTimeStamp = 0.0f;
	
	for (char c : lineI) {
		if (c != ' ') {
			tempString += c;
			//UE_LOG(LogTemp, Warning, TEXT("TempString %s"), *tempString);
		}
		else {
			tempFloat = StrToFloat(tempString);
			switch (arrayIndex) {
			case 0:
				satTimeStamp = tempFloat;
				//UE_LOG(LogTemp, Warning, TEXT("SaveTime %f"), satTimeStamp);
				break;
			case 1:
				satPosition.X = ProcessCoord(tempFloat);
				//UE_LOG(LogTemp, Warning, TEXT("SaveX %f"), satPosition.X);
				break;
			case 2:
				satPosition.Y = ProcessCoord(tempFloat);
				//UE_LOG(LogTemp, Warning, TEXT("SaveY %f"), satPosition.Y);
				break;
			case 3:
				satPosition.Z = ProcessCoord(tempFloat);
				//UE_LOG(LogTemp, Warning, TEXT("SaveZ %f"), satPosition.Z);
				break;
			default:
				//UE_LOG(LogTemp, Warning, TEXT("Add"));
				inputCoord.satInfo.Add(satTimeStamp, satPosition);
				break;
			}
			arrayIndex++;
			tempString = FString("");
		}
	}
}

//This function converts exponentials to float
float UMySatCoord::StrToFloat(FString strNum) {
	float floatNum;

	std::string stdSciNum(TCHAR_TO_UTF8(*strNum));
	std::stringstream ss(stdSciNum);

	ss >> floatNum;
	return floatNum;
}

//This function scales down the Ephemeris Coordinates
float UMySatCoord::ProcessCoord(float preProcess) {
	return preProcess /= 12000.0f;
}

