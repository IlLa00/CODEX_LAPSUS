// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CL_EquipmentCardInstance.h"
#include "Data/FCL_EquipmentCard.h"

void UCL_EquipmentCardInstance::InitFromRow(const FCL_CardRowBase& Row)
{
	Super::InitFromRow(Row);

	const FCL_EquipmentCard& EquipRow = static_cast<const FCL_EquipmentCard&>(Row);
	Stats.Strength = EquipRow.Strength;
	Stats.Agility = EquipRow.Agility;
	Stats.Intelligence = EquipRow.Intelligence;
	Stats.HP = EquipRow.HP;
	Stats.Dexterity = EquipRow.Dexterity;
}
