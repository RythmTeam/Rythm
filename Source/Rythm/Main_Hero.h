// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Warrior.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Main_Hero.generated.h"

/**
 * 
 */
UCLASS()
class RYTHM_API AMain_Hero : public AWarrior
{
	GENERATED_BODY()
public:
	AMain_Hero();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera_Component;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SpringArm")
	USpringArmComponent* SpringArm;

};
