// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"

AHero::AHero()
{
	Attack_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Attack"));
	Block_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Block"));
}
