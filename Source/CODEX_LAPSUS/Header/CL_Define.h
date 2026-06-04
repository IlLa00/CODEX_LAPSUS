// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "CL_Define.generated.h"

class ACL_SlotBase;
class ACL_CharacterBase;

UENUM()
enum ECL_SLotType
{
	NoSlot,
	DefaultSlot,
	MovableSlot,
	ActiveSlot,
	EnemySlot,
	AllySlot,
	MovementOverlaySlot,
	SpellSlot
};

UENUM()
enum ECL_PassiveAbilityUseMoment
{
	OnTurnStart,
	OnMoved,
	BeforeAttack,
	AfterAttack,
	OnKill,
	OnTurnEnd,
};

UENUM()
enum ECL_PassiveAbilityTarget
{
	Self,
	CharactersInRange,
	HitCharacters,
};

UENUM()
enum ECL_MovementType
{
	Move_Walk,
	Move_Fly,
	Move_Immobile,
};

UENUM()
enum ECL_Element
{
	Normal,
	Fire,
	Earth,
	Air,
	Water
};

// 카드 종류 - 새 종류 추가 시 여기에 확장하고 CreateFromRow 팩토리에 매핑 등록
UENUM(BlueprintType)
enum class ECL_CardType : uint8
{
	Equipment,
	Skill,
	Tool
};

// 덱 편집 UI에서 카드가 위치한 영역 (드래그 출발/도착 판정용)
UENUM(BlueprintType)
enum class ECL_CardZone : uint8
{
	Owned,
	Equipped
};

UENUM()
enum ECL_BattleState
{
	Initialization,
	DeploymentPhase,
	WaitingForPlayerAction,
	PlayerIsCastingSpell,
	PlayerIsPlaying,
	WaitingForEnemyAction,
	EnemyIsPlaying,
	Victory,
	Defeat,
	Over
};

UENUM()
enum ECL_BattleCursorType
{
	Default,
	Walk,
	Fly,
	MeleeAttack,
	RangeAttack,
	BrokenRangeAttack,
	Spell,
	Wait
};

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

USTRUCT()
struct FCL_ListOfSlots
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<TObjectPtr<ACL_SlotBase>> OverlaySlots;
};

USTRUCT()
struct FCL_PlayerCharacterData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<TObjectPtr<ACL_CharacterBase>> Characters;

	UPROPERTY()
	int32 Stack;
};

USTRUCT()
struct FCL_EnemyCharacterData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<TObjectPtr<ACL_CharacterBase>> Characters;

	UPROPERTY()
	int32 Stack;
};

USTRUCT()
struct FCL_DamageData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 Damage;

	UPROPERTY()
	int32 MinDamage;

	UPROPERTY()
	int32 MaxDamage;

	UPROPERTY()
	float DamageModifier;

	//UPROPERTY()
	//Element;


};

USTRUCT()
struct FCL_ElementReductions
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float Normal;

	UPROPERTY()
	float Fire;

	UPROPERTY()
	float Earth;

	UPROPERTY()
	float Air;

	UPROPERTY()
	float Water;
};

USTRUCT()
struct FCL_CharacterStatBuff
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float Attack;

	UPROPERTY()
	float Defense;

	UPROPERTY()
	float MinDamage;

	UPROPERTY()
	float MaxDamage;

	UPROPERTY()
	float Ammo;

	UPROPERTY()
	float MovementRange;
};