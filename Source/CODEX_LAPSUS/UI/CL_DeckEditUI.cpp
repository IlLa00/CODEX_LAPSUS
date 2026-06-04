// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CL_DeckEditUI.h"
#include "UI/CL_CardListItem.h"
#include "UI/CL_CardDragDropOperation.h"
#include "Subsystem/CL_CardSubsystem.h"
#include "Data/CL_CardInstance.h"
#include "Data/FCL_CardStatBlock.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/GameInstance.h"

void UCL_DeckEditUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (UCL_CardSubsystem* Subsystem = GetCardSubsystem())
	{
		Subsystem->OnDeckChanged.AddUniqueDynamic(this, &UCL_DeckEditUI::HandleDeckChanged);

		// 보유 목록이 비어 있으면 DataTable로 초기 적재
		if (Subsystem->GetOwnedCards().Num() == 0 && CardSourceTable)
			Subsystem->InitOwnedFromDataTable(CardSourceTable);
	}

	RefreshAll();
}

void UCL_DeckEditUI::NativeDestruct()
{
	if (UCL_CardSubsystem* Subsystem = GetCardSubsystem())
	{
		Subsystem->OnDeckChanged.RemoveDynamic(this, &UCL_DeckEditUI::HandleDeckChanged);
	}

	Super::NativeDestruct();
}

void UCL_DeckEditUI::SelectCharacter(int32 CharIndex)
{
	SelectedCharIndex = CharIndex;
	RefreshAll();
}

bool UCL_DeckEditUI::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	return Cast<UCL_CardDragDropOperation>(InOperation) != nullptr;
}

bool UCL_DeckEditUI::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UCL_CardDragDropOperation* Op = Cast<UCL_CardDragDropOperation>(InOperation);
	UCL_CardSubsystem* Subsystem = GetCardSubsystem();
	if (!Op || !Op->Card || !Subsystem)
	{
		return false;
	}

	// 커서가 어느 TileView 위인지로 도착 영역 판정
	const FVector2D ScreenPos = InDragDropEvent.GetScreenSpacePosition();
	const bool bOverEquipped = EquippedCardSlots && EquippedCardSlots->GetCachedGeometry().IsUnderLocation(ScreenPos);
	const bool bOverOwned = OwnedCardSlots && OwnedCardSlots->GetCachedGeometry().IsUnderLocation(ScreenPos);

	// 보유 -> 장착
	if (Op->SourceZone == ECL_CardZone::Owned && bOverEquipped)
		return Subsystem->EquipCard(SelectedCharIndex, Op->Card, MaxEquipSlots);

	// 장착 -> 해제
	if (Op->SourceZone == ECL_CardZone::Equipped && bOverOwned)
		return Subsystem->UnequipCard(SelectedCharIndex, Op->Card);

	return false;
}

void UCL_DeckEditUI::HandleDeckChanged()
{
	RefreshAll();
}

void UCL_DeckEditUI::RefreshAll()
{
	RefreshTileView(OwnedCardSlots, false);
	RefreshTileView(EquippedCardSlots, true);
	RefreshStats();
}

void UCL_DeckEditUI::RefreshTileView(UTileView* TileView, bool bEquipped)
{
	if (!TileView)
	{
		return;
	}

	UCL_CardSubsystem* Subsystem = GetCardSubsystem();
	if (!Subsystem)
	{
		return;
	}

	TArray<UObject*> Items;

	if (bEquipped)
	{
		for (UCL_CardInstance* Card : Subsystem->GetEquippedCards(SelectedCharIndex))
		{
			UCL_CardListItem* Item = NewObject<UCL_CardListItem>(this);
			Item->Card = Card;
			Item->Amount = 1;
			Item->Zone = ECL_CardZone::Equipped;
			Item->CharIndex = SelectedCharIndex;
			Items.Add(Item);
		}
	}
	else
	{
		for (const FCL_OwnedCard& Owned : Subsystem->GetOwnedCards())
		{
			UCL_CardListItem* Item = NewObject<UCL_CardListItem>(this);
			Item->Card = Owned.Card;
			Item->Amount = Owned.Amount;
			Item->Zone = ECL_CardZone::Owned;
			Item->CharIndex = SelectedCharIndex;
			Items.Add(Item);
		}
	}

	TileView->SetListItems(Items);
}

void UCL_DeckEditUI::RefreshStats()
{
	UCL_CardSubsystem* Subsystem = GetCardSubsystem();
	if (!Subsystem)
	{
		return;
	}

	const FCL_CardStatBlock Total = Subsystem->GetEquippedStatTotal(SelectedCharIndex);

	if (StrengthText)     
		StrengthText->SetText(FText::AsNumber(Total.Strength)); 
	if (AgilityText)      
		AgilityText->SetText(FText::AsNumber(Total.Agility));
	if (IntelligenceText) 
		IntelligenceText->SetText(FText::AsNumber(Total.Intelligence)); 
	if (HPText)           
		HPText->SetText(FText::AsNumber(Total.HP)); 
	if (DexterityText)    
		DexterityText->SetText(FText::AsNumber(Total.Dexterity)); 
}

UCL_CardSubsystem* UCL_DeckEditUI::GetCardSubsystem() const
{
	if (const UGameInstance* GI = GetGameInstance())
		return GI->GetSubsystem<UCL_CardSubsystem>();

	return nullptr;
}
