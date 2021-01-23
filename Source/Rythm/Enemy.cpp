// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Main_Hero.h"
#include "Kismet/GameplayStatics.h"
#include "AI_enemy.h"

AEnemy::AEnemy(const class FObjectInitializer& PCIP)
{
	//Pawn is automatically possessed by an AI Controller whenever it is created
	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;

	SightSphere = PCIP.CreateDefaultSubobject<USphereComponent> (this, TEXT("SightSphere"));
	SightSphere->AttachToComponent(RootComponent ,FAttachmentTransformRules::KeepRelativeTransform);
	SightSphere->SetSphereRadius(400.0f);

	Attack_Signal = false;
	Is_Waiting = false;
	Health_Value = 100.0f;
	Damage_Value = 0.0f;
	Person_Move_Speed = 15.0f;
	Attack_Frames_Amount = 20;
	Person_Name = "Enemy";
	Warrior_Attack_Cooldown = 50;
	Warrior_Block_Cooldown = 25;
}

void AEnemy::Wait_Frames(const int32& Frame_To_Wait)
{
	Waiting_Frames_Amount = Frame_To_Wait;
	Is_Waiting = true;
}

void AEnemy::Tick(float DeltaSeconds)
{
	/*
	if (Person_Name == "Enemy")
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy::Tick() begin"));
	}
	*/
	AMain_Hero *Hero = Cast<AMain_Hero>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Hero) return;
	FVector ToPlayerVector = Hero->GetActorLocation() - GetActorLocation();

	const float DistanceToPlayer = ToPlayerVector.Size();

    if( DistanceToPlayer > SightSphere->GetScaledSphereRadius() )
    {
    	GetSprite()->SetFlipbook(Idle_Animation);
    	return;
    }

	TArray<APerson*> Hittable_Person = Get_Hittable_Persons(Direction);
	int32 Count = 0;
	for (auto Iter : Hittable_Person)
	{
		Count++;
	}
	if(Count > 0) 
	{
		Attack();
	}
	
	Iterate_Combat_Status();

	ToPlayerVector.Normalize();
	ToPlayerVector.Y = ToPlayerVector.Z;
	const FVector2D Input2D(ToPlayerVector);
	PersonInput.PureMovementInput = Input2D;
	
	/*
	if (Person_Name != "Main_Hero")
	{
		UE_LOG(LogTemp, Warning, TEXT("Velocity in AEn::Tick size squared %f"),
         PersonInput.PureMovementInput.SizeSquared());
	}
	*/
	Move_By_Input(DeltaSeconds);
	Set_Status_Animation();
	Iterate_Cooldown_Status();
}

