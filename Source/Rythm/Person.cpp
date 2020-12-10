// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Person.h"

APerson::APerson()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PersonBase"));
	}
	UBoxComponent* Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetBoxExtent(FVector(5.0f, 5.0f, 5.0f));
	Collision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Collision->SetCollisionProfileName("Person");
	
	Idle_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Idle"));
    
	Running_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Run"));
    	
	Person_Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("PersonDirection"));
	Person_Direction->AttachTo(RootComponent);

	Movement_Component = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement_Component"));
	Movement_Component->SetUpdatedComponent(RootComponent);
	// Movement Preferences;
	Movement_Component->MaxSpeed = 500.0f;
	Movement_Component->Acceleration = Movement_Component->GetMaxSpeed() * 2;
	Movement_Component->Deceleration = Movement_Component->GetMaxSpeed() * 2;

	Health_Value = 0.0f;
}

// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	Super::BeginPlay();
}

void APerson::Update_Animation()
{
	const FVector Player_Velocity = GetVelocity();
	UPaperFlipbook* Desired_Animation = Player_Velocity.SizeSquared() > 0.0f ?
        Running_Animation : Idle_Animation;
	if (GetSprite()->GetFlipbook() != Desired_Animation)
	{
		GetSprite()->SetFlipbook(Desired_Animation);
	}
}

void APerson::Update_Person()
{
	// Update animation to match the motion
	Update_Animation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();	
	const float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}


// Called every frame
void APerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Update_Person();
}

void APerson::Horizontal_Movement(float value)
{
	const FVector input = FVector(value, 0.0f, 0.0f);
	AddMovementInput(input);
}

void APerson::Vertical_Movement(float value)
{
	const FVector input = FVector(0.0f, 0.0f, value);
	AddMovementInput(input);
}

// Called to bind functionality to input
void APerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &APerson::Horizontal_Movement);
	InputComponent->BindAxis("Vertical", this, &APerson::Vertical_Movement);
}