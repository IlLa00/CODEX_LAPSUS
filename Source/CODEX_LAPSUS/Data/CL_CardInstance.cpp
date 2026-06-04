// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CL_CardInstance.h"
#include "Data/FCL_CardRowBase.h"
#include "Data/CL_EquipmentCardInstance.h"

UCL_CardInstance* UCL_CardInstance::CreateFromRow(UObject* Outer, const FCL_CardRowBase& Row)
{
	UClass* InstanceClass = nullptr;
	switch (Row.CardType)
	{
	case ECL_CardType::Equipment:
		InstanceClass = UCL_EquipmentCardInstance::StaticClass();
		break;
	case ECL_CardType::Skill:
	case ECL_CardType::Tool:
	default:
		InstanceClass = UCL_CardInstance::StaticClass();
		break;
	}

	UCL_CardInstance* Instance = NewObject<UCL_CardInstance>(Outer, InstanceClass);
	Instance->InitFromRow(Row);
	return Instance;
}

void UCL_CardInstance::InitFromRow(const FCL_CardRowBase& Row)
{
	CardID = Row.CardID;
	CardType = Row.CardType;
	DisplayName = Row.DisplayName;
	Icon = Row.Icon;
	Cost = Row.Cost;
}
