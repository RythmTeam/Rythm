// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Warrior.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class RYTHM_API AEnemy : public AWarrior
{
	GENERATED_BODY()
public:
	AEnemy(const class FObjectInitializer& PCIP);

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Расстояние на котором он видит
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* SightSphere;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
};
