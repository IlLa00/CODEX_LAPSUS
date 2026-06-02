#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FCL_EquipmentCard.generated.h"

USTRUCT(BlueprintType)
struct CODEX_LAPSUS_API FCL_EquipmentCard : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCL_EquipmentCard() {}

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
};
