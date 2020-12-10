// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 
#include "GameFramework/Actor.h"
#include "Paper2D/Classes/PaperFlipbook.h"
#include "Person.generated.h"

UCLASS()
class RYTHM_API APerson : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Direction")
	class UArrowComponent* person_direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Animations")
	class UPaperFlipbook* idle_animation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Animations")
	class UPaperFlipbook* running_animation;
};
