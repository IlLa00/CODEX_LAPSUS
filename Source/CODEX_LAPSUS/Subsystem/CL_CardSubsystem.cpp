// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/CL_CardSubsystem.h"
#include "Data/CL_CardInstance.h"
#include "Data/FCL_CardRowBase.h"
#include "Engine/DataTable.h"

void UCL_CardSubsystem::InitOwnedFromDataTable(UDataTable* Table)
{
	if (!Table)
		return;

	for (const TPair<FName, uint8*>& Pair : Table->GetRowMap())
	{
		const FCL_CardRowBase* Row = reinterpret_cast<const FCL_CardRowBase*>(Pair.Value);
		if (!Row)
			continue;

		UCL_CardInstance* Card = UCL_CardInstance::CreateFromRow(this, *Row);
		AddOwnedCard(Card, 1);
	}
}

void UCL_CardSubsystem::AddOwnedCard(UCL_CardInstance* Card, int32 Count)
{
	if (!Card || Count <= 0)
		return;

	// 같은 CardID가 이미 있으면 수량만 누적
	for (FCL_OwnedCard& Owned : OwnedCards)
	{
		if (Owned.Card && Owned.Card->GetCardID() == Card->GetCardID())
		{
			Owned.Amount += Count;
			OnDeckChanged.Broadcast();
			return;
		}
	}

	FCL_OwnedCard NewEntry;
	NewEntry.Card = Card;
	NewEntry.Amount = Count;
	OwnedCards.Add(NewEntry);
	OnDeckChanged.Broadcast();
}

bool UCL_CardSubsystem::EquipCard(int32 CharIndex, UCL_CardInstance* Card, int32 MaxEquipSlots)
{
	if (!Card)
		return false;

	if (GetEquippedCount(CharIndex) >= MaxEquipSlots)
		return false;

	// 보유 수량 확인
	FCL_OwnedCard* OwnedEntry = OwnedCards.FindByPredicate([Card](const FCL_OwnedCard& O)
	{
		return O.Card && O.Card->GetCardID() == Card->GetCardID();
	});

	if (!OwnedEntry || OwnedEntry->Amount <= 0)
		return false;

	// 중복 장착 허용
	FCL_EquippedSet& Set = EquippedByCharacter.FindOrAdd(CharIndex);
	Set.Cards.Add(OwnedEntry->Card);

	ChangeOwnedAmount(OwnedEntry->Card, -1);

	OnDeckChanged.Broadcast();
	return true;
}

bool UCL_CardSubsystem::UnequipCard(int32 CharIndex, UCL_CardInstance* Card)
{
	if (!Card)
		return false;

	FCL_EquippedSet* Set = EquippedByCharacter.Find(CharIndex);
	if (!Set)
		return false;

	// 같은 CardID 중 한 장만 제거
	const int32 FoundIndex = Set->Cards.IndexOfByPredicate([Card](const UCL_CardInstance* C)
	{
		return C && C->GetCardID() == Card->GetCardID();
	});

	if (FoundIndex == INDEX_NONE)
		return false;

	UCL_CardInstance* Removed = Set->Cards[FoundIndex];
	Set->Cards.RemoveAt(FoundIndex);

	ChangeOwnedAmount(Removed, 1);

	OnDeckChanged.Broadcast();
	return true;
}

FCL_CardStatBlock UCL_CardSubsystem::GetEquippedStatTotal(int32 CharIndex) const
{
	FCL_CardStatBlock Total;

	if (const FCL_EquippedSet* Set = EquippedByCharacter.Find(CharIndex))
	{
		for (const UCL_CardInstance* Card : Set->Cards)
		{
			if (Card)
				Total += Card->GetStatContribution();
		}
	}

	return Total;
}

TArray<UCL_CardInstance*> UCL_CardSubsystem::GetEquippedCards(int32 CharIndex) const
{
	TArray<UCL_CardInstance*> Result;
	if (const FCL_EquippedSet* Set = EquippedByCharacter.Find(CharIndex))
	{
		for (const TObjectPtr<UCL_CardInstance>& Card : Set->Cards)
			Result.Add(Card);
	}
	return Result;
}

int32 UCL_CardSubsystem::GetEquippedCount(int32 CharIndex) const
{
	if (const FCL_EquippedSet* Set = EquippedByCharacter.Find(CharIndex))
		return Set->Cards.Num();

	return 0;
}

void UCL_CardSubsystem::ChangeOwnedAmount(UCL_CardInstance* Card, int32 Delta)
{
	if (!Card || Delta == 0)
		return;

	const int32 Index = OwnedCards.IndexOfByPredicate([Card](const FCL_OwnedCard& O)
	{
		return O.Card && O.Card->GetCardID() == Card->GetCardID();
	});

	if (Index != INDEX_NONE)
	{
		OwnedCards[Index].Amount += Delta;
		if (OwnedCards[Index].Amount <= 0)
			OwnedCards.RemoveAt(Index);
	}
	else if (Delta > 0)
	{
		// 해제 시 보유 목록에 없던 카드는 대표 인스턴스로 재등록
		FCL_OwnedCard NewEntry;
		NewEntry.Card = Card;
		NewEntry.Amount = Delta;
		OwnedCards.Add(NewEntry);
	}
}
