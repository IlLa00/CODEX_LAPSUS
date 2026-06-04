#pragma once

#include "CoreMinimal.h"
#include "FCL_StatBlock.generated.h"

// 캐릭터·카드가 공유하는 원시 스탯 묶음 (기획서 '스탯 종류').
// 캐릭터 기본 스탯 + 장착 카드 기여분이 같은 타입으로 합산된다.
USTRUCT(BlueprintType)
struct CODEX_LAPSUS_API FCL_StatBlock
{
	GENERATED_BODY()

public:
	// 힘(STR) - 공격력 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Strength = 0;

	// 민첩(DEX) - 명중률/회피 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Dexterity = 0;

	// 체력(CON) - 체력/방어 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Constitution = 0;

	// 저항(RES) - 상태이상 저항/회복 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Resistance = 0;

	// 행운(LUK) - 크리티컬/상태이상 적용 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Luck = 0;

	// 크리티컬 - 치명타 확률 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Critical = 0;

	FCL_StatBlock& operator+=(const FCL_StatBlock& Other)
	{
		Strength += Other.Strength;
		Dexterity += Other.Dexterity;
		Constitution += Other.Constitution;
		Resistance += Other.Resistance;
		Luck += Other.Luck;
		Critical += Other.Critical;
		return *this;
	}

	FCL_StatBlock operator+(const FCL_StatBlock& Other) const
	{
		FCL_StatBlock Result = *this;
		Result += Other;
		return Result;
	}
};
