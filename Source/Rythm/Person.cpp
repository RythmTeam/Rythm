// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APerson::APerson()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	if (!RootComponent)
    {
    	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PersonBase"));
    }
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
	
}

// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

