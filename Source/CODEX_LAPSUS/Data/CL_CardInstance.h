// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Header/CL_Define.h"
#include "Data/FCL_CardStatBlock.h"
#include "CL_CardInstance.generated.h"

struct FCL_CardRowBase;

UCLASS(BlueprintType)
class CODEX_LAPSUS_API UCL_CardInstance : public UObject
{
	GENERATED_BODY()

public:
	static UCL_CardInstance* CreateFromRow(UObject* Outer, const FCL_CardRowBase& Row);

	virtual void InitFromRow(const FCL_CardRowBase& Row);

	virtual FCL_CardStatBlock GetStatContribution() const { return FCL_CardStatBlock(); }

	UFUNCTION(BlueprintCallable, Category = "Card")
	ECL_CardType GetCardType() const { return CardType; }

	UFUNCTION(BlueprintCallable, Category = "Card")
	FName GetCardID() const { return CardID; }

	UFUNCTION(BlueprintCallable, Category = "Card")
	FText GetDisplayName() const { return DisplayName; }

	UFUNCTION(BlueprintCallable, Category = "Card")
	UTexture2D* GetIcon() const { return Icon; }

	UFUNCTION(BlueprintCallable, Category = "Card")
	int32 GetCost() const { return Cost; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Card")
	FName CardID;

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	ECL_CardType CardType = ECL_CardType::Equipment;

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	FText DisplayName;

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	int32 Cost = 0;
};
