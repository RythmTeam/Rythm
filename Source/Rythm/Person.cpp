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

void APerson::Update_Animation()
{
	const FVector2D Player_Velocity = PersonInput.PureMovementInput;
	
	UPaperFlipbook* Desired_Animation = Player_Velocity.SizeSquared() > 0.0f ?
        Running_Animation : Idle_Animation;
	if (GetSprite()->GetFlipbook() != Desired_Animation)
	{
		GetSprite()->SetFlipbook(Desired_Animation);
	}
}

void APerson::Update_Person(const float& DeltaTime)
{
	// Update animation to match the motion
	Update_Animation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector2D PlayerVelocity = PersonInput.PureMovementInput;
	/*
	if (Person_Name != "Main_Hero")
	{
		UE_LOG(LogTemp, Warning, TEXT("Velocity in Per::Upd_Pers size squared %f"),
         PersonInput.PureMovementInput.SizeSquared());
	}
	*/
	const float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Direction = false;
			GetSprite()->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Direction = true; 
			GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
	// Move person
	const float SpeedX = PlayerVelocity.X * Person_Move_Speed * DeltaTime;
	const float SpeedZ = PlayerVelocity.Y * Person_Move_Speed * DeltaTime;

	const FVector AddingInput(SpeedX, 0.0f, SpeedZ);
	Person_Movement->AddInputVector(AddingInput);
	/*
	if (Person_Name == "Enemy")
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy::Tick() end"));
	}
	*/
}


// Called every frame
void APerson::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	PersonInput.Sanitize();
	//UE_LOG(LogTemp, Warning, TEXT("Movement input: (%f, %f)"),
	//	PersonInput.PureMovementInput.X, PersonInput.PureMovementInput.Y);

	Update_Person(DeltaTime);
}

void APerson::Horizontal_Movement(float Value)
{
	PersonInput.MoveHorizontal(Value);
}

void APerson::Vertical_Movement(float Value)
{
	PersonInput.MoveVertical(Value);
}

// Called to bind functionality to input
void APerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &APerson::Horizontal_Movement);
	InputComponent->BindAxis("Vertical", this, &APerson::Vertical_Movement);
}
