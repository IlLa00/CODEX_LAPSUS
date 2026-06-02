// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CL_CardInstance.h"
#include "Data/FCL_CardStatBlock.h"
#include "CL_EquipmentCardInstance.generated.h"

UCLASS(BlueprintType)
class CODEX_LAPSUS_API UCL_EquipmentCardInstance : public UCL_CardInstance
{
	GENERATED_BODY()

public:
	virtual void InitFromRow(const FCL_CardRowBase& Row) override;

	virtual FCL_CardStatBlock GetStatContribution() const override { return Stats; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	FCL_CardStatBlock Stats;
};
