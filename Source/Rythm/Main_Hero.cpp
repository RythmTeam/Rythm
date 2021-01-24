// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Hero.h"
#include "GameFramework/SpringArmComponent.h"

AMain_Hero::AMain_Hero()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 2.0f;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	
	Camera_Component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera_Component->bUsePawnControlRotation = false;
	Camera_Component->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera_Component->OrthoWidth = 2048.0f;
	Camera_Component->AspectRatio = 3.0f / 4.0f;
	Camera_Component->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	Camera_Component->AttachToComponent(SpringArm,
		FAttachmentTransformRules::KeepRelativeTransform,
		USpringArmComponent::SocketName);

	Attack_Frames_Amount = 23;
	Block_Frames_Amount = 16;
	Health_Value = 100.0f;
	Person_Move_Speed = 20.0f;
	Damage_Value = 10.0f;
	Person_Name = "Main_Hero";
	Warrior_Attack_Cooldown = 50;
	Warrior_Block_Cooldown = 25;
}
