// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


#include "Person_With_Camera.generated.h"

/**
 * 
 */
UCLASS()
class RYTHM_API APerson_With_Camera : public APerson
{
	GENERATED_BODY()
public:
	APerson_With_Camera();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Camera")
	UCameraComponent* Camera_Component;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Camera")
	USpringArmComponent* SpringArm;
};
