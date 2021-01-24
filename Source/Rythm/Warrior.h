// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "Components/BoxComponent.h"
#include "Warrior.generated.h"

/**
 * 
 */
UCLASS()
class RYTHM_API AWarrior : public APerson
{
	// Warrior is a person so it has:
	// Collision profile, can move and has 2 represents of statuses
	// So he has a direction of view
	// Warrior can attack and block attacks
	// Warrior has a damage;

	//TODO: change number of block frames
	//TODO: Block
	GENERATED_BODY()

protected:
	int Current_Attack_Frame;
	int Current_Block_Frame;

	int32 Attack_Frames_Amount;
	int32 Block_Frames_Amount;
	int32 Damage_Value;
	int32 Attack_Cooldown_Frames;
	int32 Block_Cooldown_Frames;
	int32 Warrior_Attack_Cooldown;
	int32 Warrior_Block_Cooldown;
	
	bool Is_Warrior_Started_Attack;
	bool Is_Warrior_Started_Block;
	bool Is_Warrior_Stopped_Attack;
	bool Is_Warrior_Stopped_Block;
	
public:
	AWarrior();
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook* Attack_Animation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook* Block_Animation;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	UBoxComponent* Right_Block;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	UBoxComponent* Left_Block;
	
	UFUNCTION()
	virtual void Attack();

	UFUNCTION()
	virtual void Block();

	virtual bool Is_Warrior_Blocking() override;

	UFUNCTION()
	virtual void Iterate_Combat_Status();

	UFUNCTION()
	virtual void Iterate_Cooldown_Status();

	virtual void Set_Status_Animation() override;

	UFUNCTION()
	virtual TArray<APerson*> Get_Hittable_Persons(const bool& Block);

	// Called every frame
	// Overrides to add attack & block animations

	// Overrides to add attack & block actions;
	virtual void Tick(float DeltaTime) override;
	
	//Overrides to add attack & block actions
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
