#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FCL_StatStatusCoeffRow.generated.h"

// 스탯 → 스테이터스 변환 계수 (행렬형 DataTable의 한 행).
// RowName = 스탯 키(STR/DEX/CON/RES/LUK/CRIT), 각 열 = 해당 스탯 1당 스테이터스 기여 계수.
// 예) RowName=STR, Attack=0.2  → 힘 1당 공격력 +0.2
USTRUCT(BlueprintType)
struct CODEX_LAPSUS_API FCL_StatStatusCoeffRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coeff")
	float Attack = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coeff")
	float Defense = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coeff")
	float Health = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coeff")
	float Accuracy = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coeff")
	float Evasion = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coeff")
	float Cost = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coeff")
	float Block = 0.f;
};
