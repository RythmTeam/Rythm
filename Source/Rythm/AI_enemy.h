// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "AIController.h"
#include "AI_enemy.generated.h"

/**
 * 
 */

 UCLASS()
class RYTHM_API AAI_enemy : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	virtual  void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
protected:
	// Our pawn, pre-cast to a Enemy. Will be NULL if the pawn is NULL or is not a Enemy.
	UPROPERTY(BlueprintReadOnly, Category = "Enemy")
	AEnemy* PawnAsEnemy;
	
};
