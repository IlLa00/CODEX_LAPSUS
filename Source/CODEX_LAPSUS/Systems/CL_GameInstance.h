// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Header/CL_Define.h"
#include "CL_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CODEX_LAPSUS_API UCL_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	bool bShouldLoadGame;
	bool bShouldLoadTransform;
	bool bShouldLoadEnemyPawns;
	bool bShouldAddExp;
	FString SlotName;
	FCL_EnemyCharacterData EnemyCharacterList;
};
