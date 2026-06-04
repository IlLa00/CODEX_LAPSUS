// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CL_CardEntryWidget.h"
#include "UI/CL_CardListItem.h"
#include "UI/CL_CardDragDropOperation.h"
#include "Data/CL_CardInstance.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UCL_CardEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	BoundItem = Cast<UCL_CardListItem>(ListItemObject);
	if (!BoundItem || !BoundItem->Card)
	{
		return;
	}

	UCL_CardInstance* Card = BoundItem->Card;

	if (NameText)
	{
		NameText->SetText(Card->GetDisplayName());
	}
	if (CostText)
	{
		CostText->SetText(FText::AsNumber(Card->GetCost()));
	}
	if (TypeText)
	{
		TypeText->SetText(FText::AsNumber(static_cast<int32>(Card->GetCardType())));
	}
	if (AmountText)
	{
		// 수량은 보유 영역에서만 의미가 있으므로 장착 영역에서는 숨긴다
		if (BoundItem->Zone == ECL_CardZone::Owned)
		{
			AmountText->SetVisibility(ESlateVisibility::HitTestInvisible);
			AmountText->SetText(FText::AsNumber(BoundItem->Amount));
		}
		else
		{
			AmountText->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (IconImage)
	{
		if (UTexture2D* Icon = Card->GetIcon())
		{
			IconImage->SetBrushFromTexture(Icon);
		}
	}
}

FReply UCL_CardEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UCL_CardEntryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (!BoundItem || !BoundItem->Card)
	{
		return;
	}

	UCL_CardDragDropOperation* Op = NewObject<UCL_CardDragDropOperation>();
	Op->Card = BoundItem->Card;
	Op->SourceZone = BoundItem->Zone;
	Op->SourceCharIndex = BoundItem->CharIndex;

	// 원본(this)은 리스트에 그대로 남기고, 커서를 따라다닐 드래그 비주얼은 별도 복제본을 만든다.
	// (DefaultDragVisual = this 로 두면 원본 SWidget이 데코레이터로 옮겨가 리스트에서 사라질 수 있다.)
	UCL_CardEntryWidget* Visual = CreateWidget<UCL_CardEntryWidget>(GetOwningPlayer(), GetClass());
	if (Visual)
	{
		Visual->NativeOnListItemObjectSet(BoundItem);
		Op->DefaultDragVisual = Visual;
	}

	// 드래그 중 원본 슬롯을 반투명 처리/복원하기 위해 원본 엔트리를 오퍼레이션에 실어 보낸다.
	Op->SourceEntry = this;
	Op->Pivot = EDragPivot::MouseDown;

	OutOperation = Op;
}
