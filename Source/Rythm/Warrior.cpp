// Fill out your copyright notice in the Description page of Project Settings.


#include "Warrior.h"

AWarrior::AWarrior()
{
	Attack_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Attack"));
	Block_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Block"));
	Damage_Value = 0.0f;
}

void AWarrior::Attack()
{
	
}

void AWarrior::Block()
{
	
}

void AWarrior::Update_Animation()
{
	
}

void AWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &APerson::Horizontal_Movement);
	InputComponent->BindAxis("Vertical", this, &APerson::Vertical_Movement);
	// TODO: bind action
}

