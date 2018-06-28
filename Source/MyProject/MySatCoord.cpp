// Fill out your copyright notice in the Description page of Project Settings.

#include "MySatCoord.h"
#include "Misc/FileHelper.h"
#include "GenericPlatform/GenericPlatform.h"
#include "HAL/PlatformFilemanager.h"
#include "Containers/UnrealString.h"


IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

//This function reads the .sa file and return info to a map
TArray<FSatInfoEphemeris> UMySatCoord::LoadCoord(FString path) {

	TArray<FString> arr;
	if (PlatformFile.FileExists(*path)) {
		FFileHelper::LoadFileToStringArray(arr, *path);
	}

	bool startParse = false;
	int8 tempArrayIndex;
	FString satName = "NEOSSAT";
	FSatInfoEphemeris inputCoord; //Coordinates read from file directly, in ephemeris format
	//FSatInfo satCoord; //Processed coordinates
	TMap<FString, FSatInfoEphemeris> satInfo;

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

			tempArrayIndex = 0;

			for (char c : arr[i]) {

				switch (tempArrayIndex) {
					case 0: inputCoord.eTime += c;
						break;
					case 1: inputCoord.ePosX += c;
						break;
					case 2: inputCoord.ePosY += c;
						break;
					case 3: inputCoord.ePosZ += c;
						break;
				}
				tempArrayIndex++;
			}

			satInfo.Add(satName, inputCoord);

		}
	}
	
	return satInfo.FindRef(satName);
}

//function to process coordinates
