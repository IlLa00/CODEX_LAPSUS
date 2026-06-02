// Fill out your copyright notice in the Description page of Project Settings.


#include "Units/CL_UnitBase.h"

// Sets default values
ACL_UnitBase::ACL_UnitBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACL_UnitBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACL_UnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

