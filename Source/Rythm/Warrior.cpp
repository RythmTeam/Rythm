// Fill out your copyright notice in the Description page of Project Settings.

#include "Warrior.h"
#include "PaperFlipbookComponent.h"


AWarrior::AWarrior()
{
	Is_Warrior_Started_Attack = false;
	Is_Warrior_Started_Block = false;
	Is_Warrior_Stopped_Attack = true;
	Is_Warrior_Stopped_Block = true;

	Current_Block_Frame = 0;
	Current_Attack_Frame = 0;

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

void AWarrior::Set_Status_Animation()
{
	if (Current_Status == "Idle")
	{
		GetSprite()->SetFlipbook(Idle_Animation);
	}
	else if (Current_Status == "Run")
	{
		GetSprite()->SetFlipbook(Running_Animation);
	}
	else if (Current_Status == "Attack")
	{
		GetSprite()->SetFlipbook(Attack_Animation);
	}
	else if (Current_Status == "Block")
	{
		GetSprite()->SetFlipbook(Block_Animation);
	}
	if (Direction)
	{
		GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else
	{
		GetSprite()->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	}
}

void AWarrior::Iterate_Cooldown_Status()
{
	if (Attack_Cooldown_Frames > 0)
	{
		Attack_Cooldown_Frames--;
	}
	if (Block_Cooldown_Frames > 0)
	{
		Block_Cooldown_Frames--;
	}
}

void AWarrior::Attack()
{
	if (Attack_Cooldown_Frames == 0)
	{
		Is_Warrior_Started_Attack = true;
		Is_Warrior_Stopped_Attack = false;
		Current_Status = "Attack";
		Is_Status_Change_Locked = true;
		Is_Movement_Locked = true;
		UE_LOG(LogTemp, Warning, TEXT("Dealed Damage"));
	
		// Hits all overlapped persons
		TArray<APerson*> Hittable_Persons = Get_Hittable_Persons(Direction);
	
		for (auto Iter : Hittable_Persons)
		{
			if (!Iter->Is_Warrior_Blocking())
			{
				Iter->Take_Damage(Damage_Value);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Successfully blocked damage!"));
			}
		}
		Attack_Cooldown_Frames = Warrior_Attack_Cooldown;
	}
}

void AWarrior::Block()
{
	if (Block_Cooldown_Frames == 0)
	{
		Is_Warrior_Started_Block = true;
		Is_Warrior_Stopped_Block = false;
		Current_Status = "Block";
		Is_Status_Change_Locked = true;
		Is_Movement_Locked = true;
		UE_LOG(LogTemp, Warning, TEXT("Block Damage"));
	}
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
		if(Current_Attack_Frame == Attack_Frames_Amount)
		{
			Is_Warrior_Stopped_Attack = true;
			Is_Warrior_Started_Attack = false;
			Is_Status_Change_Locked = false;
			Is_Movement_Locked = false;
			Current_Attack_Frame = 0;
		}
		else Current_Attack_Frame++;
		/*
		if (Person_Name == "Enemy")
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack frame %i"),
             Current_Attack_Frame);
		}
		*/
	}
	else if (Is_Warrior_Started_Block)
	{
		if(Current_Block_Frame == Block_Frames_Amount)
		{
			Is_Warrior_Stopped_Block = true;
			Is_Warrior_Started_Block = false;
			Is_Status_Change_Locked = false;
			Is_Movement_Locked = false;
			Current_Block_Frame = 0;
		}
		else Current_Block_Frame++;
	}
}

void AWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Iterate_Combat_Status();
	// Update_Person(DeltaTime);
	Iterate_Combat_Status();
	Move_By_Input(DeltaTime);
	Set_Status_Animation();
	Iterate_Cooldown_Status();
}

void AWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &APerson::Horizontal_Input);
	InputComponent->BindAxis("Vertical", this, &APerson::Vertical_Input);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AWarrior::Attack);
	InputComponent->BindAction("Block", IE_Pressed, this, &AWarrior::Block);
}
