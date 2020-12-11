// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperFlipbookComponent.h"
#include "Warrior.h"

AWarrior::AWarrior()
{
	Attack_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Attack"));
	Block_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Block"));
	Damage_Value = 0.0f;
	Is_Warrior_Started_Attack = false;
	Is_Warrior_Started_Block = false;
	Is_Warrior_Stopped_Attack = true;
	Is_Warrior_Stopped_Block = true;
}

void AWarrior::Attack()
{
	Is_Warrior_Started_Attack = true;
	Is_Warrior_Stopped_Attack = false;
}

void AWarrior::Block()
{
	Is_Warrior_Started_Block = true;
	Is_Warrior_Stopped_Block = false;
}

void AWarrior::Update_Animation()
{
	UPaperFlipbook* Desired_Animation;
	if(!Is_Warrior_Stopped_Attack)
	{
		Desired_Animation = Attack_Animation;
	}
	else if(!Is_Warrior_Started_Block)
	{
		Desired_Animation = Block_Animation;
	}
	else
	{
		const FVector Player_Velocity = GetVelocity();
		Desired_Animation = Player_Velocity.SizeSquared() > 0.0f ?
            Running_Animation : Idle_Animation->GetFlipbook();
	}
	if (GetSprite()->GetFlipbook() != Desired_Animation)
	{
		GetSprite()->SetFlipbook(Desired_Animation);
	}
}

void AWarrior::Tick(float DeltaTime)
{
	static int32 Attack_Frames = 0;
	// TODO: Change Number of Block Frames
	static int32 Block_Frames = 0;
	if(Is_Warrior_Started_Attack)
	{
		if(Attack_Frames == 23)
		{
			Is_Warrior_Stopped_Attack = true;
			Is_Warrior_Started_Attack = false;
			Attack_Frames = 0;
		}
		else Attack_Frames++;
	}
	else if (Is_Warrior_Started_Block)
	{
		if(Block_Frames == 10)
		{
			Is_Warrior_Stopped_Attack = true;
			Is_Warrior_Started_Block = false;
			Block_Frames = 0;
		}
		else Block_Frames++;
	}
	
	Update_Animation();
}

void AWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &APerson::Horizontal_Movement);
	InputComponent->BindAxis("Vertical", this, &APerson::Vertical_Movement);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AWarrior::Attack);
	InputComponent->BindAction("Block", IE_Pressed, this, &AWarrior::Block);
}

