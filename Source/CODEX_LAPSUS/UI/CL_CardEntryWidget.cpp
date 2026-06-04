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
	Op->DefaultDragVisual = this;
	Op->Pivot = EDragPivot::MouseDown;

	OutOperation = Op;
}
