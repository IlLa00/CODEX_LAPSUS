// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CL_StatEffectRow.h"
#include "Components/TextBlock.h"

void UCL_StatEffectRow::SetRow(const FText& StatName, int32 Value)
{
	if (StatNameText)
	{
		StatNameText->SetText(StatName);
	}

	if (StatValueText)
	{
		const FString Prefix = (Value > 0) ? TEXT("+") : TEXT("");
		StatValueText->SetText(FText::FromString(Prefix + FString::FromInt(Value)));
	}
}
