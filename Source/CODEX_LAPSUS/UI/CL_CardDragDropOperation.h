// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Header/CL_Define.h"
#include "CL_CardDragDropOperation.generated.h"

class UCL_CardInstance;

UCLASS()
class CODEX_LAPSUS_API UCL_CardDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Card")
	TObjectPtr<UCL_CardInstance> Card = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Card")
	ECL_CardZone SourceZone = ECL_CardZone::Owned;

	UPROPERTY(BlueprintReadWrite, Category = "Card")
	int32 SourceCharIndex = 0;
};
