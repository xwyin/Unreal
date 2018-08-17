// Fill out your copyright notice in the Description page of Project Settings.

#include "MyLoadConfig.h"
#include "Misc/ConfigCacheIni.h"

UMyLoadConfig::UMyLoadConfig() {
	/*
	if (!GConfig->FindConfigFileWithBaseName("SaPath"))
	{
		SaveConfig(); // Creates the config file and writes the class default values
	}
	*/
	FString GLoadOptionsIni = FPaths::GeneratedConfigDir().Append(TEXT("Windows/SaPath.ini"));

	if (GConfig) {
		GConfig->GetString(
			TEXT("/Script/MyProject.MyLoadConfig"),
			TEXT("path"),
			path,
			GLoadOptionsIni
		);
		//UE_LOG(LogTemp, Warning, TEXT("SA File Path: %s"), *path);
	}
}

FString UMyLoadConfig::GetSaPath() {
	return path;
}



