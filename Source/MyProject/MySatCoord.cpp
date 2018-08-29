// Fill out your copyright notice in the Description page of Project Settings.


#include "MySatCoord.h"
#include "Engine.h"
#include "MyLoadConfig.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatform.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/FileManagerGeneric.h"
#include "Containers/UnrealString.h"
#include <sstream>    
#include <string>


IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

/* 
**This function picks up all the .sa files from path specified by user using config file "SaPath.ini"
**Then calls SaveSatInfo() to save info for each file
*/
void UMySatCoord::ReadAllFiles() {
	//UE_LOG(LogTemp, Warning, TEXT("Calling ReadAllFiles()"));
	FFileManagerGeneric fileManager;
	fileManager.SetSandboxEnabled(true);

	FString identifier = FString("*.sa");

	UMyLoadConfig *loadConfig = NewObject<UMyLoadConfig>();
	FString path = FPaths::Combine(loadConfig->GetSaPath(), identifier);

	fileManager.FindFiles(fileNames, *path, true, false);
	//UE_LOG(LogTemp, Warning, TEXT("This many files: %d"), fileNames.Num());

	for (int8 i = 0; i < fileNames.Num(); i++) {
		FString fullPath = FPaths::Combine(loadConfig->GetSaPath(), fileNames[i]);
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
		if (arr[i] == "BEGIN Ephemeris") {
			//UE_LOG(LogTemp, Warning, TEXT("Time: %s"), *arr[i + 4]);
			startTime = ParseTime(arr[i+4]);
		}
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
	return ephemeris /= 6000.0f;
}

TArray<FVector> UMySatCoord::GetSpecificSatInfo(FString satName) {
	//UE_LOG(LogTemp, Warning, TEXT("Called GetSpecificSatInfo()"));
	TArray<FVector> *result = satDatabase.Find(satName);
	checkf(result, TEXT("Return specific sat failed"));
	return *result;
}

TMap<FString, TArray<FVector>> UMySatCoord::GetAllSatInfoNoWrap() {
	return satDatabase;
}

TMap<FString, FArrayWrapper> UMySatCoord::GetAllSatInfo() {
	TMap<FString, FArrayWrapper> wrappedMap;
	for(auto& Elem : satDatabase)
	{
		wrappedMap.Add(Elem.Key, FArrayWrapper(Elem.Value));
	}
	return wrappedMap;
}

FDateTime UMySatCoord::ParseTime(FString lineI) {

	lineI += FString(" ");

	//Need to optimize this.. use C++ libraries like boost
	MonthMap.Add(FString("Jan"), FString("01"));
	MonthMap.Add(FString("Feb"), FString("02"));
	MonthMap.Add(FString("Mar"), FString("03"));
	MonthMap.Add(FString("Apr"), FString("04"));
	MonthMap.Add(FString("May"), FString("05"));
	MonthMap.Add(FString("Jun"), FString("06"));
	MonthMap.Add(FString("Jul"), FString("07"));
	MonthMap.Add(FString("Aug"), FString("08"));
	MonthMap.Add(FString("Sep"), FString("09"));
	MonthMap.Add(FString("Oct"), FString("10"));
	MonthMap.Add(FString("Nov"), FString("11"));
	MonthMap.Add(FString("Dec"), FString("12"));

	int8 arrayIndex = 0;
	int32 dayInt;
	FString tempString;
	FString day;
	FString month;
	FString year;
	FString time;
	FString sStartTime;
	FString left;
	FString right;

	for (char c : lineI) {
		if (c != ' ') {
			tempString += c;
		}
		else {
			switch (arrayIndex) {
			case 0:
				break;
			case 12:
				//UE_LOG(LogTemp, Warning, TEXT("day: %s"), *tempString);
				//dayInt = static_cast<int8>(std::stoi(TCHAR_TO_UTF8(*tempString)));
				dayInt = FCString::Atoi(*tempString);
				if (dayInt < 10) {
					day = FString("0") + FString::FromInt(dayInt);
				}
				break;
			case 13:
				//UE_LOG(LogTemp, Warning, TEXT("month: %s"), *tempString);
				month = *MonthMap.Find(tempString);
				break;
			case 14:
				//UE_LOG(LogTemp, Warning, TEXT("year: %s"), *tempString);
				year = tempString;
				break;
			case 15:
				//UE_LOG(LogTemp, Warning, TEXT("time: %s"), *tempString);
				tempString.Split(TEXT("."), &left, &right);
				time = left;
				break;
			}
			arrayIndex++;
			tempString = FString("");
		}
	}
	sStartTime = year + '.' + month + '.' + day + '-' + time;
	UE_LOG(LogTemp, Warning, TEXT("Time in String format: %s"), *sStartTime);
	FDateTime::Parse(sStartTime, startTime);
	return startTime;
}

FDateTime UMySatCoord::GetStartTime() {
	return startTime;
}
