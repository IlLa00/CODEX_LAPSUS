// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CL_StatEffectRow.generated.h"

class UTextBlock;

UCLASS()
class CODEX_LAPSUS_API UCL_StatEffectRow : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Card")
	void SetRow(const FText& StatName, int32 Value);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StatNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StatValueText;
};
