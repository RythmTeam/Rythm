// Fill out your copyright notice in the Description page of Project Settings.

#include "Warrior.h"
#include "PaperFlipbookComponent.h"


AWarrior::AWarrior()
{
	//Attack_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Attack"));
	//Block_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Block"));
	Is_Warrior_Started_Attack = false;
	Is_Warrior_Started_Block = false;
	Is_Warrior_Stopped_Attack = true;
	Is_Warrior_Stopped_Block = true;

	Block_Frames = 0;
	Attack_Frames = 0;
	
	Right_Block = CreateDefaultSubobject<UBoxComponent>(TEXT("Block_1"));
	Right_Block->SetRelativeLocation(FVector(75.0f, 0.0f, 0.0f));
	Right_Block->SetBoxExtent(FVector(40.0f, 40.0f, 40.0f));
	Right_Block->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	Left_Block = CreateDefaultSubobject<UBoxComponent>(TEXT("Block_2"));
	Left_Block->SetRelativeLocation(FVector(-75.0f, 0.0f, 0.0f));
	Left_Block->SetBoxExtent(FVector(40.0f, 40.0f, 40.0f));
	Left_Block->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

TArray<APerson*> AWarrior::Get_Hittable_Persons(const bool& Block)
{
	TArray<AActor*> Raw_Result;
	if (Block)
	{
		Right_Block->GetOverlappingActors(Raw_Result, APerson::StaticClass());
	}
	else
	{
		Left_Block->GetOverlappingActors(Raw_Result, APerson::StaticClass());
	}
	TArray<APerson*> Pure_Result;
	for (auto& Iter : Raw_Result)
	{
		APerson* Some_Overlapped_Person = Cast<APerson>(Iter);
		Pure_Result.Add(Some_Overlapped_Person);
	}
	return Pure_Result;
}

void AWarrior::Attack()
{
	Is_Warrior_Started_Attack = true;
	Is_Warrior_Stopped_Attack = false;
	UE_LOG(LogTemp, Warning, TEXT("Dealed Damage"));
	// Hits all overlapped persons

	TArray<APerson*> Hittable_Persons = Get_Hittable_Persons(Direction);
	
	for (auto Iter : Hittable_Persons)
	{
		Iter->Take_Damage(Damage_Value);
	}
}

void AWarrior::Block()
{
	Is_Warrior_Started_Block = true;
	Is_Warrior_Stopped_Block = false;
}

bool AWarrior::Is_Warrior_Blocking()
{
	return Is_Warrior_Started_Block;
}

// TODO: Change Number of Block Frames
void AWarrior::Iterate_Combat_Status()
{
	if(Is_Warrior_Started_Attack)
	{
		if(Attack_Frames == Attack_Frames_Amount)
		{
			Is_Warrior_Stopped_Attack = true;
			Is_Warrior_Started_Attack = false;
			Attack_Frames = 0;
		}
		else Attack_Frames++;
	}
	else if (Is_Warrior_Started_Block)
	{
		if(Block_Frames == Block_Frames_Amount)
		{
			Is_Warrior_Stopped_Block = true;
			Is_Warrior_Started_Block = false;
			Block_Frames = 0;
		}
		else Block_Frames++;
	}
}

void AWarrior::Update_Animation()
{
	UPaperFlipbook* Desired_Animation;
	if(!Is_Warrior_Stopped_Attack)
	{
		Desired_Animation = Attack_Animation;
	}
	else if(!Is_Warrior_Stopped_Block)
	{
		Desired_Animation = Block_Animation;
	}
	else
	{
		const FVector2D Player_Velocity = PersonInput.PureMovementInput;
		/*
		if (Person_Name != "Main_Hero")
		{
			UE_LOG(LogTemp, Warning, TEXT("Velocity in AW::Upd_Anim size squared %f"),
             PersonInput.PureMovementInput.SizeSquared());
		}
		*/
		Desired_Animation = Player_Velocity.SizeSquared() > 0.0f ?
            Running_Animation : Idle_Animation;
	}
	if (GetSprite()->GetFlipbook() != Desired_Animation)
	{
		GetSprite()->SetFlipbook(Desired_Animation);
	}
}

void AWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Iterate_Combat_Status();
	
	Update_Person(DeltaTime);
}

void AWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &APerson::Horizontal_Movement);
	InputComponent->BindAxis("Vertical", this, &APerson::Vertical_Movement);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AWarrior::Attack);
	InputComponent->BindAction("Block", IE_Pressed, this, &AWarrior::Block);
}
