// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Header/CL_Define.h"
#include "CL_CardListItem.generated.h"

class UCL_CardInstance;

UCLASS(BlueprintType)
class CODEX_LAPSUS_API UCL_CardListItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Card")
	TObjectPtr<UCL_CardInstance> Card = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	int32 Amount = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	ECL_CardZone Zone = ECL_CardZone::Owned;

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	int32 CharIndex = 0;
};
