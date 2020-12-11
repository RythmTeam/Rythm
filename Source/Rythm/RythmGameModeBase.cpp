// Copyright Epic Games, Inc. All Rights Reserved.


#include "RythmGameModeBase.h"

#include "Main_Hero.h"

ARythmGameModeBase::ARythmGameModeBase()
{
	DefaultPawnClass = ConstructorHelpers::FClassFinder<AMain_Hero>(
		TEXT("/Content/Blueprints/Main_Hero_BP")).Class;
}

