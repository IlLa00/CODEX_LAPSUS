// Fill out your copyright notice in the Description page of Project Settings.


#include "Heroes/CL_HeroBase.h"

// Sets default values
ACL_HeroBase::ACL_HeroBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACL_HeroBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACL_HeroBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

