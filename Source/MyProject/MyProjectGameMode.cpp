// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectPawn.h"

AMyProjectGameMode::AMyProjectGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = AMyProjectPawn::StaticClass();
}
