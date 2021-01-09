// Fill out your copyright notice in the Description page of Project Settings.

//#include "Main_Hero.h"
#include "AI_enemy.h"
#include "Enemy.h"




 void AAI_enemy::Tick(float DeltaTime)
{
	if(PawnAsEnemy)
	{
/*
		if(AActor* Target=PawnAsEnemy->GetTarget())
		{
			// We do have a target. Shamble toward it and attempt violence! У нас есть цель. Тащитесь к нему и пытайтесь насилие!
			FVector DirectionToTarget = (Target->GetActorLocation() - PawnAsEnemy->GetActorLocation()).GetSafeNormal2D();
			float DotToTarget = FVector::DotProduct(DirectionToTarget, PawnAsEnemy->GetActorForwardVector());
			float SidewaysDotToTarget = FVector::DotProduct(DirectionToTarget, PawnAsEnemy->GetActorRightVector());
			float DeltaYawDesired = FMath::Atan2(SidewaysDotToTarget, DotToTarget);
		}
		*/
	}
}

void AAI_enemy::OnPossess(APawn* InPawn)
{
	Super::Possess(InPawn);
	PawnAsEnemy = Cast<AEnemy>(GetPawn());
}

void AAI_enemy::OnUnPossess()
{
	Super::UnPossess();
	PawnAsEnemy = nullptr;
}

