// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tarea1_TSubclassOffGameMode.h"
#include "Tarea1_TSubclassOffCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATarea1_TSubclassOffGameMode::ATarea1_TSubclassOffGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
