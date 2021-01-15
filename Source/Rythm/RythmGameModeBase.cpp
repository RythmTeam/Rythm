// Copyright Epic Games, Inc. All Rights Reserved.


#include "RythmGameModeBase.h"

#include "Main_Hero.h"

ARythmGameModeBase::ARythmGameModeBase()
{
	DefaultPawnClass = ConstructorHelpers::FClassFinder<AMain_Hero>(
		TEXT("/Game/Blueprints/AMain_Hero_BP")).Class;
}

