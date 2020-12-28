// Fill out your copyright notice in the Description page of Project Settings.

#include "Main_Hero.h"
#include "AI_enemy.h"
#include "Enemy.h"



AEnemy::AEnemy()
{
	//Pawn is automatically possessed by an AI Controller whenever it is created
	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;
	Health_Value = 100.0f;
	Damage_Value = 10.0f;
}

void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}



void AEnemy::SetTarget(AActor* NewTarget)
{
	TargetActor=NewTarget;
	TargetHero= Cast<AMain_Hero>(NewTarget);
}

AActor* AEnemy::GetTarget()
{
	return TargetActor;
}

AMain_Hero* AEnemy::GetTargetAsHero()
{
	return TargetHero; 
}
