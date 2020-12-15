// Copyright Epic Games, Inc. All Rights Reserved.


#include "RythmGameModeBase.h"

#include "Main_Hero.h"
#include "Person_With_Camera.h"

ARythmGameModeBase::ARythmGameModeBase()
{
	DefaultPawnClass = ConstructorHelpers::FClassFinder<APerson_With_Camera>(
		TEXT("/Game/Blueprints/MyPerson_With_Camera_BP")).Class;
}

