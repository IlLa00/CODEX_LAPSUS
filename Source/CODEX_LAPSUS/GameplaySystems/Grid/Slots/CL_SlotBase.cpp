// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplaySystems/Grid/Slots/CL_SlotBase.h"

// Sets default values
ACL_SlotBase::ACL_SlotBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACL_SlotBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACL_SlotBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

