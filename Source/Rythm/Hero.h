// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "Hero.generated.h"

/**
 * 
 */
UCLASS()
class RYTHM_API AHero : public APerson
{
	GENERATED_BODY()

public:
	AHero();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* Attack_Animation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* Block_Animation;

	// Camera - ?
};
