#pragma once

#include "CoreMinimal.h"
#include "FCL_StatusBlock.generated.h"

// 스탯에서 파생된 최종 스테이터스 묶음 (기획서 캐릭터 기본 스테이터스).
// 명중률/회피는 퍼센트 의미, 나머지는 수치. (코스트/막기는 현재 공식 미정 → 0)
USTRUCT(BlueprintType)
struct CODEX_LAPSUS_API FCL_StatusBlock
{
	GENERATED_BODY()

public:
	// 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Attack = 0.f;

	// 방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Defense = 0.f;

	// 체력(최종 HP)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Health = 0.f;

	// 명중률 (%)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Accuracy = 0.f;

	// 회피 (%)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Evasion = 0.f;

	// 코스트 (공식 미정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Cost = 0.f;

	// 막기 (공식 미정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float Block = 0.f;
};
