// Fill out your copyright notice in the Description page of Project Settings.

#include "MySatCoord.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatform.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/FileManagerGeneric.h"
#include "Containers/UnrealString.h"
#include <sstream>	
#include <string>


IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

void UMySatCoord::ReadAllFiles() {

	TArray<FString> fileNames;
	
	FFileManagerGeneric fileManager;
	fileManager.SetSandboxEnabled(true);
	FString extension = FString("*.sa");
	FString path = FPaths::Combine(FPaths::ProjectDir(),TEXT("STKOutputData"),extension);
	
	//UE_LOG(LogTemp, Warning, TEXT("FolderPath: %s"), *path);

	fileManager.FindFiles(fileNames, *path, true, false);

	//UE_LOG(LogTemp, Warning, TEXT("NumFiles: %d"), fileNames.Num());

	for (int8 i = 0 ; i < fileNames.Num() ; i++) {
		//UE_LOG(LogTemp, Warning, TEXT("FileName: %s"), *fileNames[i]);
		SaveSatInfo
	}
	
}

//This function reads the .sa file and return info as a map
TArray<FVector> UMySatCoord::SaveSatInfo(FString path) {
	TArray<FString> arr;
	if (PlatformFile.FileExists(*path)) {
		FFileHelper::LoadFileToStringArray(arr, *path);
	}

	bool startParse = false;
	FString satName = "NEOSSAT";
	TArray<FVector> inputCoord; 
	TMap<FString, TArray<FVector>> satDatabase; //final map where information of all satellites are stored

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

		if (startParse) {
			ParseCoord(inputCoord,arr[i]);
		}
	}
	satDatabase.Add(satName, inputCoord);
	//UE_LOG(LogTemp, Warning, TEXT("This many sat: %d"), satDatabase.Num());
	//UE_LOG(LogTemp, Warning, TEXT("This many records: %d"), inputCoord.Num());
	return *satDatabase.Find(satName);
}

//This function parses time and position information of satellite
void UMySatCoord::ParseCoord(TArray<FVector> &inputCoord, FString lineI) {
	int8 arrayIndex = 0;
	FString tempString;
	float tempFloat;
	FVector satPosition;
	
	for (char c : lineI) {
		if (c != ' ') {
			tempString += c;
		}
		else {
			tempFloat = StrToFloat(tempString);
			switch (arrayIndex) {
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
			case 4:
				inputCoord.Add(satPosition);
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

