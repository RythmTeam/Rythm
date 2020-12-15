// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Warrior.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Warrior_With_Camera.generated.h"

/**
 * 
 */
UCLASS()
class RYTHM_API AWarrior_With_Camera : public AWarrior
{
	GENERATED_BODY()
public:
	AWarrior_With_Camera();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Camera")
	UCameraComponent* Camera_Component;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Camera")
	USpringArmComponent* SpringArm;
};
