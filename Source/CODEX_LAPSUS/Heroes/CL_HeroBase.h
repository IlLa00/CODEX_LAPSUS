// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CL_HeroBase.generated.h"

UCLASS()
class CODEX_LAPSUS_API ACL_HeroBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACL_HeroBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	FText Name;
	UPROPERTY()
	TObjectPtr<UTexture2D> Portrait;
	UPROPERTY()
	TObjectPtr<UTexture2D> DetailImage;
	UPROPERTY()
	FName ProjectileSpawnSocket;
	UPROPERTY()
	int32 Gold;
	UPROPERTY()
	int32 MaxMana;
	UPROPERTY()
	int32 CurrentMana;
	UPROPERTY()
	int32 Level;
	UPROPERTY()
	bool bCanUseSpell;

};
