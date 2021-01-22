// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Warrior.h"
#include "Components/SphereComponent.h"
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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* SightSphere;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	virtual void Wait_Frames(const int32& Frame_To_Wait);
protected:

	bool Attack_Signal;
	bool Is_Waiting;
	int32 Waiting_Frames_Amount;
};
