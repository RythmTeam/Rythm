// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"

#include "GameFramework/SpringArmComponent.h"

AHero::AHero()
{
	Attack_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Attack"));
	Block_Animation = CreateDefaultSubobject<UPaperFlipbook>(TEXT("Block"));

	//Camera Preferences
	USpringArmComponent* Spring_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Spring_Arm->TargetArmLength = 500.0f;
	Spring_Arm->bEnableCameraLag = true;
	Spring_Arm->bEnableCameraRotationLag = false;
	Spring_Arm->CameraLagSpeed = 2.0f;
	Spring_Arm->bDoCollisionTest = false;
	Spring_Arm->bUsePawnControlRotation = false;
	Spring_Arm->AttachTo(RootComponent);
	Spring_Arm->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	Camera_Component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera_Component->bUsePawnControlRotation = false;
	Camera_Component->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera_Component->OrthoWidth = 1024.0f;
	Camera_Component->AspectRatio = 3.0f / 4.0f;
	Camera_Component->AttachTo(Spring_Arm, USpringArmComponent::SocketName);
	Camera_Component->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));
}
