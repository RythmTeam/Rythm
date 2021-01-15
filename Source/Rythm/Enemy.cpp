// Fill out your copyright notice in the Description page of Project Settings.

#include "Main_Hero.h"
#include "AI_enemy.h"

#include "Enemy.h"



AEnemy::AEnemy(const class FObjectInitializer& PCIP)
{
	//Pawn is automatically possessed by an AI Controller whenever it is created
	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;

	SightSphere = PCIP.CreateDefaultSubobject<USphereComponent> (this, TEXT("SightSphere"));
	SightSphere->AttachTo(RootComponent);
	AttackRangeSphere = PCIP.CreateDefaultSubobject <USphereComponent>(this, TEXT("AttackRangeSphere"));
	AttackRangeSphere->AttachTo( RootComponent );

	Health_Value = 100.0f;
	Damage_Value = 10.0f;
	Person_Move_Speed = 80.0f;
	Attack_Frames_Amount = 9;
	Person_Name = "Enemy";
}

void AEnemy::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
	
	// базовый интеллект: двигает монстра на игрока
	AMain_Hero *Hero = Cast<AMain_Hero>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0) );
	if( !Hero ) return;
	FVector toPlayer = Hero->GetActorLocation() - GetActorLocation();

	float distanceToPlayer = toPlayer.Size();
    // Если игрок не в SightSphere монстра,
    // идём назад
    if( distanceToPlayer > SightSphere->GetScaledSphereRadius() )
    {
    // Если игрок в не поля зрения,
    // то монстр не может гнаться за ним	
    return;
    }
	
	toPlayer /= distanceToPlayer;
	//toPlayer.Normalize(); // reduce to unit vector

	
	// Собственно двигаем монстра на игрока
// TODO: uncommend AddMovementInput
	// AddMovementInput(toPlayer, Person_Move_Speed*DeltaSeconds);
	// Обращение лицом к цели
	// Получаете ротатор для поворачивания того,
	// что смотрит в направлении игрока `toPlayer`
	FRotator toPlayerRotation = toPlayer.Rotation();
	toPlayerRotation.Pitch = 0; // 0 off the pitch
	RootComponent->SetWorldRotation( toPlayerRotation );
	GetSprite()->SetFlipbook(Running_Animation);
	//Update_Person(DeltaSeconds);


	//Update_Animation();
}

