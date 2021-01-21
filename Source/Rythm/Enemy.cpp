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

	Health_Value = 100.0f;
	Damage_Value = 10.0f;
	Person_Move_Speed = 20.0f;
	Attack_Frames_Amount = 9;
	Person_Name = "Enemy";
}

void AEnemy::Tick( float DeltaSeconds )
{
	/*
	if (Person_Name == "Enemy")
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy::Tick() begin"));
	}
	*/
	AMain_Hero *Hero = Cast<AMain_Hero>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0) );
	if( !Hero ) return;
	FVector ToPlayer = Hero->GetActorLocation() - GetActorLocation();

	const float distanceToPlayer = ToPlayer.Size();

    if( distanceToPlayer > SightSphere->GetScaledSphereRadius() )
    {
    	GetSprite()->SetFlipbook(Idle_Animation);
    	return;
    }
	
	ToPlayer.Normalize();

	ToPlayer.Y = ToPlayer.Z;
	const FVector2D Input2D(ToPlayer);
	PersonInput.PureMovementInput = Input2D;
	/*
	if (Person_Name != "Main_Hero")
	{
		UE_LOG(LogTemp, Warning, TEXT("Velocity in AEn::Tick size squared %f"),
         PersonInput.PureMovementInput.SizeSquared());
	}
	*/
	Update_Person(DeltaSeconds);
}

