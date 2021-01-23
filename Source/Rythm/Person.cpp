// Fill out your copyright notice in the Description page of Project Settings.

#include "Person.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"

//////////////////////// Person Input Custom Component
void FPersonInput::MoveHorizontal(const float Value)
{
	RawMovementInput.X += Value;
}

void FPersonInput::MoveVertical(const float Value)
{
	RawMovementInput.Y += Value;
}

void FPersonInput::LockMovement()
{
	Is_Move_Locked = true;
}

void FPersonInput::UnlockMovement()
{
	Is_Move_Locked = false;
}

FPersonInput::FPersonInput()
{
	Is_Move_Locked = false;
}

void FPersonInput::Sanitize()
{
	PureMovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	PureMovementInput = PureMovementInput.GetSafeNormal();
	RawMovementInput.Set(0.0f, 0.0f);
}
////////////////////////

APerson::APerson()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->DestroyComponent();
	GetCharacterMovement()->SetActive(false);

	Person_Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

	Current_Status = "Idle";
	Is_Status_Change_Locked = false;
}

void APerson::Move_By_Input(const float& DeltaTime)
{
	if (Is_Movement_Locked)
	{
		PersonInput.PureMovementInput.Set(0.0f, 0.0f);
		if (!Is_Status_Change_Locked) Current_Status = "Idle";
	}
	else
	{
		const FVector2D PlayerVelocity = PersonInput.PureMovementInput;
		const float SpeedX = PlayerVelocity.X * Person_Move_Speed * DeltaTime;
		const float SpeedZ = PlayerVelocity.Y * Person_Move_Speed * DeltaTime;
		/*
		if (Person_Name == "Main_Hero")
		{
			UE_LOG(LogTemp, Warning, TEXT("Speeds by input (%f, %f)"),
             SpeedX, SpeedZ);
		}
		*/
		const float TravelDirection = PlayerVelocity.X;
		
		if (TravelDirection < 0.0f) Direction = false;
		else if (TravelDirection > 0.0f) Direction = true; 

		const FVector AddingInput(SpeedX, 0.0f, SpeedZ);
		if (AddingInput.SizeSquared() == 0)
		{
			if (!Is_Status_Change_Locked) Current_Status = "Idle";
		}
		else
		{
			Person_Movement->AddInputVector(AddingInput);
			if (!Is_Status_Change_Locked) Current_Status = "Run";
		}
	}
}

void APerson::Set_Status_Animation()
{
	if (Current_Status == "Idle")
	{
		GetSprite()->SetFlipbook(Idle_Animation);
	}
	else if (Current_Status == "Run")
	{
		GetSprite()->SetFlipbook(Running_Animation);
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

// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	Super::BeginPlay();
}

void APerson::Death()
{
	this->Destroy();
}

void APerson::Take_Damage(const float Taken_Damage)
{
	Health_Value -= Taken_Damage;
	UE_LOG(LogTemp, Warning, TEXT("Got Damage %s"), *Person_Name);
	if (Health_Value <= 0)
	{
		Death();
	}
}

// Called every frame
void APerson::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	PersonInput.Sanitize();
	//UE_LOG(LogTemp, Warning, TEXT("Movement input: (%f, %f)"),
	//	PersonInput.PureMovementInput.X, PersonInput.PureMovementInput.Y);

	Move_By_Input(DeltaTime);
	Set_Status_Animation();
}

void APerson::Horizontal_Input(float Value)
{
	PersonInput.MoveHorizontal(Value);
}

void APerson::Vertical_Input(float Value)
{
	PersonInput.MoveVertical(Value);
}

// Called to bind functionality to input
void APerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &APerson::Horizontal_Input);
	InputComponent->BindAxis("Vertical", this, &APerson::Vertical_Input);
}
