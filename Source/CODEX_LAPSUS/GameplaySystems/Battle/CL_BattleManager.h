// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Header/CL_Define.h"
#include "CL_BattleManager.generated.h"

class ACL_GridBase;
class ACL_CharacterBase;

UCLASS()
class CODEX_LAPSUS_API ACL_BattleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACL_BattleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
	TObjectPtr<ACL_GridBase> Grid;

	//UPROPERTY()
	//AILogic;

	int32 rangePenaltyDistance;
	bool bUseManaForUnitAbilities;

	TObjectPtr<USoundBase> BattleTheme;
	TObjectPtr<USoundBase> VictoryTheme;
	TObjectPtr<USoundBase> DefeatTheme;

private:
	//battleState;

	TArray<TObjectPtr<ACL_CharacterBase>> PlayerCharacters;
	TArray<TObjectPtr<ACL_CharacterBase>> EnemyCharacters;

	int32 CurrentTurn;

	int32 PlayCharacterIndex;

	TArray<TObjectPtr<ACL_CharacterBase>> ReadyToPlayCharacters;
	TArray<TObjectPtr<ACL_CharacterBase>> PlayedCharacters;
	TArray<TObjectPtr<ACL_CharacterBase>> WaitingCharacters;
	TObjectPtr<ACL_CharacterBase> PlayingCharacter;
	TObjectPtr<ACL_CharacterBase> MainTargetCharacter;
	TArray<TObjectPtr<ACL_CharacterBase>> TargetCharacters;
	int32 passiveAbilityIndex;
	int32 DOTIndex;
	//TMap<TObjectPtr<CL_CharacterBase>, > damageDealt
};
