// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplaySystems/Camera/CL_PlayerBattleCamera.h"

// Sets default values
ACL_PlayerBattleCamera::ACL_PlayerBattleCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACL_PlayerBattleCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACL_PlayerBattleCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACL_PlayerBattleCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

