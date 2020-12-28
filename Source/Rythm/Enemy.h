// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Warrior.h"
#include "Main_Hero.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class RYTHM_API AEnemy : public AWarrior
{
	GENERATED_BODY()
public:
	AEnemy();

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Установите цель этого злодея. Базовая версия этой функции будет обрабатывать обновление TargetActor и TargetHero соответствующим образом. Входной параметр может иметь значение NULL.
	UFUNCTION(BlueprintCallable, Category = "AI")
    void SetTarget(AActor* NewTarget);
	
	// Return the target Actor. Returning NULL indicates no target.Возвращаем целевого Актера. Возвращение NULL указывает на отсутствие цели.
	UFUNCTION(BlueprintCallable, Category = "AI")
    AActor* GetTarget();

	/* Если возможно
	, верните целевого Актера как Танка. Возвращение NULL указывает на отсутствие цели или на то, что цель не является Танком.*/
	UFUNCTION(BlueprintCallable, Category = "AI")
    AMain_Hero* GetTargetAsHero();
	
	
private:
	/* The actor we're targeting. Will be NULL if there is no target. */
	UPROPERTY(VisibleInstanceOnly, Category = "AI")
	AActor* TargetActor;

	/*Актер, на которого мы нацелены, преобразуется в Героя и кешируется. Будет NULL, если нет цели или если целевой актер не является Героем. */
	UPROPERTY(VisibleInstanceOnly, Category = "AI")
	AMain_Hero* TargetHero;


	

};
