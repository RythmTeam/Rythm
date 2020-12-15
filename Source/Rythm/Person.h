// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
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
private:
	
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

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Characters")
	float Person_MoveSpeed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Characters")
	int32 Health_Value;
	    
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Idle_Animation;
    
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Running_Animation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UArrowComponent* Person_Direction;

	UFUNCTION()
    void Vertical_Movement(float Value);

	UFUNCTION()
    void Horizontal_Movement(float Value);

	UFUNCTION()
    virtual void Update_Animation();

	UFUNCTION()
	void Update_Person(const float& DeltaTime);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Person Input")
	FPersonInput PersonInput;

};
