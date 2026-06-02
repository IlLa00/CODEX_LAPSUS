// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CL_DeckEditUI.generated.h"

class UTileView;
class UTextBlock;
class UImage;
class UDataTable;
class UCL_CardSubsystem;

/**
 * 전투 전 덱 편집 화면. 보유<->장착 드래그앤드롭과 즉시 갱신을 담당.
 */
UCLASS()
class CODEX_LAPSUS_API UCL_DeckEditUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// 캐릭터 슬롯 버튼이 호출 (선택 캐릭터 전환)
	UFUNCTION(BlueprintCallable, Category = "Deck")
	void SelectCharacter(int32 CharIndex);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	// 장착 슬롯 최대치 — 기획자가 클래스 디폴트에서 조절 (기본 5, 확장 7)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck", meta = (ClampMin = "1", ClampMax = "7"))
	int32 MaxEquipSlots = 5;

	// 보유 카드 초기 적재용 DataTable (DT_EquipmentCard 등)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck")
	TObjectPtr<UDataTable> CardSourceTable;

	// BindWidget — 실제 WBP_DeckEditUI 위젯 변수명과 일치해야 함
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> EquippedCardSlots;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> OwnedCardSlots;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> StrengthText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> AgilityText;
	
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> IntelligenceText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> HPText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> DexterityText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UImage> SelectedCharacterImage;

private:
	UFUNCTION()
	void HandleDeckChanged();

	void RefreshAll();
	void RefreshTileView(UTileView* TileView, bool bEquipped);
	void RefreshStats();

	UCL_CardSubsystem* GetCardSubsystem() const;

	UPROPERTY()
	int32 SelectedCharIndex = 0;
};
