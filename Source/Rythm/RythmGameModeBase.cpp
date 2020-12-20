// Copyright Epic Games, Inc. All Rights Reserved.


#include "RythmGameModeBase.h"

#include "Main_Hero.h"
#include "Person_With_Camera.h"
#include "Warrior_With_Camera.h"

ARythmGameModeBase::ARythmGameModeBase()
{
	DefaultPawnClass = ConstructorHelpers::FClassFinder<AMain_Hero>(
		TEXT("/Game/Blueprints/Main_Hero_BP")).Class;
}

