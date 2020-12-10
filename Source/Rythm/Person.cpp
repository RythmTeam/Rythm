// Fill out your copyright notice in the Description page of Project Settings.

#include "Person.h"

#include "Components/ArrowComponent.h"

// Sets default values
APerson::APerson()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PersonBase"));
	}
	idle_animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Idle"));

	running_animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Run"));
	
	person_direction = CreateDefaultSubobject<UArrowComponent>(TEXT("PersonDirection"));
	person_direction->AttachTo(RootComponent);	
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

