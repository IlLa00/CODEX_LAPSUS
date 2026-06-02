#pragma once

#include "CoreMinimal.h"
#include "FCL_CardStatBlock.generated.h"

USTRUCT(BlueprintType)
struct CODEX_LAPSUS_API FCL_CardStatBlock
{
	GENERATED_BODY()

public:
	// 힘 - 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Strength = 0;

	// 민첩 - 이동 코스트 소모 감소 및 이동 반경 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Agility = 0;

	// 지능 - 스킬 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Intelligence = 0;

	// HP - 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 HP = 0;

	// 손재주 - 코스트 회복량
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Dexterity = 0;

	FCL_CardStatBlock& operator+=(const FCL_CardStatBlock& Other)
	{
		Strength += Other.Strength;
		Agility += Other.Agility;
		Intelligence += Other.Intelligence;
		HP += Other.HP;
		Dexterity += Other.Dexterity;
		return *this;
	}

	FCL_CardStatBlock operator+(const FCL_CardStatBlock& Other) const
	{
		FCL_CardStatBlock Result = *this;
		Result += Other;
		return Result;
	}
};
