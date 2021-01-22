// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Person.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FPersonInput
{
	GENERATED_BODY()
public:
	FVector2D PureMovementInput;
	void Sanitize();
	void MoveHorizontal(float Value);
	void MoveVertical(float Value);
	void LockMovement();
	void UnlockMovement();
	FPersonInput();

private:
	bool Is_Move_Locked;
	FVector2D RawMovementInput;
};

UCLASS()
class RYTHM_API APerson : public APaperCharacter
{
	// Person obeys orders of PaperCharacter
	// Person can move and has 2 represents of current statuses with flipbooks
	// Person is a physical object, so it has collision profile
	// Person has a direction of gaze, so it has arrow component
	GENERATED_BODY()	
public:
	// Sets default values for this pawn's properties
	APerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Health Value
	float Health_Value;
	// Move speed
	float Person_Move_Speed;
	// Name
	FString Person_Name;
	// Direction of looking
	bool Direction;
	// True == right
	// False == left
	
public:
	
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Idle_Animation;
    
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Running_Animation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UFloatingPawnMovement* Person_Movement;
//////////////_Damage_logic___
	UFUNCTION()
	void Take_Damage(const float Taken_Damage);

	UFUNCTION()
	virtual void Death();
//////////////________________
//////////////_Movement_Logic_
	UFUNCTION()
    void Vertical_Movement(float Value);

	UFUNCTION()
    void Horizontal_Movement(float Value);
//////////////_________________
//////////////_Animation_Logic_
	UFUNCTION()
    virtual void Update_Animation();

	UFUNCTION()
	void Update_Person(const float& DeltaTime);
//////////////_________________

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Person Input")
	FPersonInput PersonInput;

};
