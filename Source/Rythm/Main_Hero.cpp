// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Main_Hero.h"

AMain_Hero::AMain_Hero()
{
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 2.0f;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->AttachTo(RootComponent);
	SpringArm->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	Camera_Component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera_Component->bUsePawnControlRotation = false;
	Camera_Component->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera_Component->OrthoWidth = 1024.0f;
	Camera_Component->AspectRatio = 3.0f / 4.0f;
	Camera_Component->AttachTo(SpringArm, USpringArmComponent::SocketName);
	Camera_Component->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	Health_Value = 100.0f;
	Damage_Value = 10.0f;

	Idle_Animation->SetFlipbook(ConstructorHelpers::FObjectFinder<UPaperFlipbook>
		(TEXT("/Game/Flipbooks/Main_Hero_Idle_flipbook")).Object);
}
