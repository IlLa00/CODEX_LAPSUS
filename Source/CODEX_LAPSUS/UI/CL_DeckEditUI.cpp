// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CL_DeckEditUI.h"
#include "UI/CL_CardListItem.h"
#include "UI/CL_CardEntryWidget.h"
#include "UI/CL_CardDragDropOperation.h"
#include "UI/CL_StatEffectRow.h"
#include "Subsystem/CL_CardSubsystem.h"
#include "Data/CL_CardInstance.h"
#include "Data/FCL_StatBlock.h"
#include "Data/FCL_StatusBlock.h"
#include "Data/CL_StatLibrary.h"
#include "Components/TileView.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
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

	UCL_CardDragDropOperation* Op = Cast<UCL_CardDragDropOperation>(InOperation);
	if (!Op)
	{
		return false;
	}

	// 매 프레임 호출되므로 AddUnique로 중복 바인딩을 막기
	Op->OnDrop.AddUniqueDynamic(this, &UCL_DeckEditUI::HandleDragFinished);
	Op->OnDragCancelled.AddUniqueDynamic(this, &UCL_DeckEditUI::HandleDragFinished);

	// 커서를 따라다니는 복제 비주얼이 아닌, 리스트에 그대로 남아있는 원본 엔트리를 반투명 처리.
	UCL_CardEntryWidget* OriginEntry = Op->SourceEntry;
	if (FadedEntry.Get() != OriginEntry)
	{
		RestoreFadedEntry();
		if (OriginEntry)
		{
			OriginEntry->SetRenderOpacity(DraggedSlotOpacity);
			FadedEntry = OriginEntry;
		}
	}

	return true;
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

void UCL_DeckEditUI::HandleDragFinished(UDragDropOperation* /*Operation*/)
{
	RestoreFadedEntry();
}

void UCL_DeckEditUI::RestoreFadedEntry()
{
	if (UCL_CardEntryWidget* Entry = FadedEntry.Get())
		Entry->SetRenderOpacity(1.0f);

	FadedEntry.Reset();
}

void UCL_DeckEditUI::RefreshAll()
{
	RefreshTileView(OwnedCardSlots, false);
	RefreshTileView(EquippedCardSlots, true);
	RefreshStats();
	RefreshEquippedEffects();
}

void UCL_DeckEditUI::RefreshTileView(UTileView* TileView, bool bEquipped)
{
	if (!TileView)
		return;

	UCL_CardSubsystem* Subsystem = GetCardSubsystem();
	if (!Subsystem)
		return;

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
		return;

	// 캐릭터 스테이터스 = 최종 파생값. 입력 스탯 = 캐릭터 기본 스탯(현재 0) + 장착 카드 스탯.
	const FCL_StatBlock TotalStats = Subsystem->GetEquippedStatTotal(SelectedCharIndex);
	const FCL_StatusBlock Status = UCL_StatLibrary::ComputeStatus(TotalStats, StatStatusCoeffTable);

	// 명중률/회피는 퍼센트, 나머지는 수치 (소수 셋째자리 버림)
	if (AttackText)
		AttackText->SetText(FText::FromString(FormatStatusValue(Status.Attack, false)));
	if (DefenseText)
		DefenseText->SetText(FText::FromString(FormatStatusValue(Status.Defense, false)));
	if (HealthText)
		HealthText->SetText(FText::FromString(FormatStatusValue(Status.Health, false)));
	if (AccuracyText)
		AccuracyText->SetText(FText::FromString(FormatStatusValue(Status.Accuracy, true)));
	if (EvasionText)
		EvasionText->SetText(FText::FromString(FormatStatusValue(Status.Evasion, true)));
	if (CostText)
		CostText->SetText(FText::FromString(FormatStatusValue(Status.Cost, false)));
	if (BlockText)
		BlockText->SetText(FText::FromString(FormatStatusValue(Status.Block, false)));
}

void UCL_DeckEditUI::RefreshEquippedEffects()
{
	if (!EquipEffectBox)
		return;

	// 매 갱신마다 기존 행을 비우고 다시 만든다 (기여한 스탯만 동적으로 표시)
	EquipEffectBox->ClearChildren();

	if (!StatEffectRowClass)
		return;

	UCL_CardSubsystem* Subsystem = GetCardSubsystem();
	if (!Subsystem)
		return;

	// 장착카드 스탯 = 카드 기여분 (장착 카드 스탯 합산)
	const FCL_StatBlock C = Subsystem->GetEquippedStatTotal(SelectedCharIndex);

	// 캐논 순서(힘→민첩→체력→저항→행운→크리티컬) + 한국어 이름.
	const TPair<FText, int32> Rows[] =
	{
		TPair<FText, int32>(FText::FromString(TEXT("힘")),       C.Strength),
		TPair<FText, int32>(FText::FromString(TEXT("민첩")),     C.Dexterity),
		TPair<FText, int32>(FText::FromString(TEXT("체력")),     C.Constitution),
		TPair<FText, int32>(FText::FromString(TEXT("저항")),     C.Resistance),
		TPair<FText, int32>(FText::FromString(TEXT("행운")),     C.Luck),
		TPair<FText, int32>(FText::FromString(TEXT("크리티컬")), C.Critical),
	};

	for (const TPair<FText, int32>& Row : Rows)
	{
		// 기여가 0인 스탯은 줄을 만들지 않는다
		if (Row.Value == 0)
			continue;

		UCL_StatEffectRow* RowWidget = CreateWidget<UCL_StatEffectRow>(this, StatEffectRowClass);
		if (!RowWidget)
			continue;

		RowWidget->SetRow(Row.Key, Row.Value);
		EquipEffectBox->AddChildToVerticalBox(RowWidget);
	}
}

FString UCL_DeckEditUI::FormatStatusValue(float Value, bool bPercent)
{
	// 소수 셋째자리 버림 = 소수 2자리 유지 (ex. 1.191 → 1.19)
	const float Truncated = FMath::TruncToFloat(Value * 100.f) / 100.f;
	FString Text = FString::Printf(TEXT("%.2f"), Truncated);
	if (bPercent)
		Text += TEXT("%");

	return Text;
}

UCL_CardSubsystem* UCL_DeckEditUI::GetCardSubsystem() const
{
	if (const UGameInstance* GI = GetGameInstance())
		return GI->GetSubsystem<UCL_CardSubsystem>();

	return nullptr;
}
