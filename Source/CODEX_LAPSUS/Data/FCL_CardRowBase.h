#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Header/CL_Define.h"
#include "FCL_CardRowBase.generated.h"

USTRUCT(BlueprintType)
struct CODEX_LAPSUS_API FCL_CardRowBase : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCL_CardRowBase() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FName CardID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int32 Cost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ECL_CardType CardType = ECL_CardType::Equipment;
};
