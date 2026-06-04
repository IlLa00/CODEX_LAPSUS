// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/FCL_StatBlock.h"
#include "Data/FCL_StatusBlock.h"
#include "CL_StatLibrary.generated.h"

class UDataTable;

UCLASS()
class CODEX_LAPSUS_API UCL_StatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Stat")
	static FCL_StatusBlock ComputeStatus(const FCL_StatBlock& Stats, const UDataTable* CoeffTable);
};
