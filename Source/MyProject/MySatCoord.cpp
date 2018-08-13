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

/* This function picks up all the .sa files from folder "/Unreal/STKOutputData" 
** Then calls SaveSatInfo() to save info for each file
*/
void UMySatCoord::ReadAllFiles() {
	TArray<FString> fileNames;
	FFileManagerGeneric fileManager;
	fileManager.SetSandboxEnabled(true);
	FString identifier = FString("*.sa");
	FString path = FPaths::Combine(FPaths::ProjectDir(), TEXT("STKOutputData"), identifier);

	fileManager.FindFiles(fileNames, *path, true, false);

	for (int8 i = 0; i < fileNames.Num(); i++) {
		FString fullPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("STKOutputData/")) + fileNames[i];
		SaveSatInfo(fullPath);
	}
}

//This function reads the .sa file and save info to the map <Name,Coordinates>
void UMySatCoord::SaveSatInfo(FString path) {

	//UE_LOG(LogTemp, Warning, TEXT("FullPath: %s"), *path);

	TArray<FString> arr;
	FString satName = FPaths::GetBaseFilename(path);
	bool startParse = false;
	TArray<FVector> inputCoord;

	if (PlatformFile.FileExists(*path)) {
		//UE_LOG(LogTemp, Warning, TEXT("File exists"));
		FFileHelper::LoadFileToStringArray(arr, *path);
	}
	
	for (int32 i = 0; i < arr.Num(); i++) {
		if (arr[i] == "EphemerisTimePosVel") {
			startParse = true;
		}
		if (arr[i] == "END Ephemeris") {
			break;
			//UE_LOG(LogTemp, Warning, TEXT("Done Parsing"));
		}
		if (startParse) {
			ParseCoord(inputCoord, arr[i]);
		}
	}
	satDatabase.Add(satName, inputCoord);
	
	//UE_LOG(LogTemp, Warning, TEXT("Size of InputCoord: %i"), inputCoord.Num());
	//UE_LOG(LogTemp, Warning, TEXT("This many sat: %i"), satDatabase.Num());
	//UE_LOG(LogTemp, Warning, TEXT("SatName: %s"), *satName);
}

//This function parses time and position info of satellite
void UMySatCoord::ParseCoord(TArray<FVector> &inputCoord, FString lineI) {

	//UE_LOG(LogTemp, Warning, TEXT("Calling ParseCoord()"));

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
				//UE_LOG(LogTemp, Warning, TEXT("Add SatPosition"));
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
float UMySatCoord::ProcessCoord(float ephemeris) {
	return ephemeris /= 12000.0f;
}

TArray<FVector> UMySatCoord::GetSpecificSatInfo(FString satName) {
	return *satDatabase.Find(satName);
}
