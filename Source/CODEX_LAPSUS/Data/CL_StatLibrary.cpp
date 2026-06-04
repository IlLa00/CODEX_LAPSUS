// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CL_StatLibrary.h"
#include "Data/FCL_StatStatusCoeffRow.h"
#include "Engine/DataTable.h"

namespace
{
	// 한 스탯의 계수 행과 스탯값을 스테이터스에 누적
	void AccumulateStatus(FCL_StatusBlock& Out, const FCL_StatStatusCoeffRow& Coeff, int32 StatValue)
	{
		const float V = static_cast<float>(StatValue);
		Out.Attack   += Coeff.Attack   * V;
		Out.Defense  += Coeff.Defense  * V;
		Out.Health   += Coeff.Health   * V;
		Out.Accuracy += Coeff.Accuracy * V;
		Out.Evasion  += Coeff.Evasion  * V;
		Out.Cost     += Coeff.Cost     * V;
		Out.Block    += Coeff.Block    * V;
	}
}

FCL_StatusBlock UCL_StatLibrary::ComputeStatus(const FCL_StatBlock& Stats, const UDataTable* CoeffTable)
{
	FCL_StatusBlock Result;

	if (!CoeffTable)
		return Result;

	// 데이터테이블 RowName이 이 키와 일치해야 함.
	const TPair<FName, int32> StatRows[] =
	{
		TPair<FName, int32>(TEXT("STR"),  Stats.Strength),
		TPair<FName, int32>(TEXT("DEX"),  Stats.Dexterity),
		TPair<FName, int32>(TEXT("CON"),  Stats.Constitution),
		TPair<FName, int32>(TEXT("RES"),  Stats.Resistance),
		TPair<FName, int32>(TEXT("LUK"),  Stats.Luck),
		TPair<FName, int32>(TEXT("CRIT"), Stats.Critical),
	};

	static const FString Context(TEXT("ComputeStatus"));
	for (const TPair<FName, int32>& StatRow : StatRows)
	{
		if (const FCL_StatStatusCoeffRow* Coeff = CoeffTable->FindRow<FCL_StatStatusCoeffRow>(StatRow.Key, Context, false))
		{
			AccumulateStatus(Result, *Coeff, StatRow.Value);
		}
	}

	return Result;
}
