// Fill out your copyright notice in the Description page of Project Settings.


#include "Warrior_With_Camera.h"

AWarrior_With_Camera::AWarrior_With_Camera()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 2.0f;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
	
	Camera_Component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera_Component->bUsePawnControlRotation = false;
	Camera_Component->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera_Component->OrthoWidth = 2048.0f;
	Camera_Component->AspectRatio = 3.0f / 4.0f;
	Camera_Component->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	Camera_Component->AttachToComponent(SpringArm,
        FAttachmentTransformRules::KeepRelativeTransform,
        USpringArmComponent::SocketName);
}
