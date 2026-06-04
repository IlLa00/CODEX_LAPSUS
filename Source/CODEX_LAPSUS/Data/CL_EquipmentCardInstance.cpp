// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CL_EquipmentCardInstance.h"
#include "Data/FCL_EquipmentCard.h"

void UCL_EquipmentCardInstance::InitFromRow(const FCL_CardRowBase& Row)
{
	Super::InitFromRow(Row);

	const FCL_EquipmentCard& EquipRow = static_cast<const FCL_EquipmentCard&>(Row);
	Stats.Strength = EquipRow.Strength;
	Stats.Dexterity = EquipRow.Dexterity;
	Stats.Constitution = EquipRow.Constitution;
	Stats.Resistance = EquipRow.Resistance;
	Stats.Luck = EquipRow.Luck;
	Stats.Critical = EquipRow.Critical;
}
