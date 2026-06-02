// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CL_CharacterBase.h"

// Sets default values
ACL_CharacterBase::ACL_CharacterBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACL_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACL_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

