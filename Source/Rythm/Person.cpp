// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Person.h"

//////////////////////// Person Input Custom Component
void FPersonInput::MoveHorizontal(const float Value)
{
	RawMovementInput.X += Value;
}

void FPersonInput::MoveVertical(const float Value)
{
	RawMovementInput.Y += Value;
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
	const float TravelDirection = PlayerVelocity.X;;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			GetSprite()->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
			UE_LOG(LogTemp, Warning, TEXT("Rotated"));
		}
		else if (TravelDirection > 0.0f)
		{
			GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			UE_LOG(LogTemp, Warning, TEXT("Straight"));
		}
	}
	// Move person
	//FVector Position = GetActorLocation();
	const float SpeedX = PlayerVelocity.X * Person_MoveSpeed * DeltaTime;
	const float SpeedZ = PlayerVelocity.Y * Person_MoveSpeed * DeltaTime;
	//Position.X += SpeedX;
	//Position.Z += SpeedZ;
	const FVector AddingInput(SpeedX, 0.0f, SpeedZ);
	Person_Movement->AddInputVector(AddingInput);
	UE_LOG(LogTemp, Warning, TEXT("New Position (%f, %f, %f)"), SpeedX, SpeedZ);
	//SetActorLocation(Position);
}


// Called every frame
void APerson::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	PersonInput.Sanitize();
	UE_LOG(LogTemp, Warning, TEXT("Movement input: (%f, %f)"),
		PersonInput.PureMovementInput.X, PersonInput.PureMovementInput.Y);

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