// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "CL_Define.generated.h"

USTRUCT()
struct FCL_SlotSPrite
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> DefaultSlotSprite;
	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> MovableSlotSprite;
	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> ActiveSlotSprite;
	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> EnemySlotSprite;
	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> AllySlotSprite;
	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> MovementOverlaySlotSprite;
	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> SpellSlotSprite;
};

USTRUCT()
struct FCL_CharacterStat
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 Attack;
	UPROPERTY()
	int32 Defense;
	UPROPERTY()
	int32 Power;
	UPROPERTY()
	int32 Knowledge;
};