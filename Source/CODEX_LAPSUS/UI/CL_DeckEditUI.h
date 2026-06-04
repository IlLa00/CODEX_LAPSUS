// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Templates/SubclassOf.h"
#include "CL_DeckEditUI.generated.h"

class UTileView;
class UTextBlock;
class UImage;
class UVerticalBox;
class UDataTable;
class UCL_CardSubsystem;
class UCL_CardEntryWidget;
class UCL_StatEffectRow;
class UDragDropOperation;

UCLASS()
class CODEX_LAPSUS_API UCL_DeckEditUI : public UUserWidget
{
	GENERATED_BODY()

public:
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

	// 드래그 중 원본 슬롯에 적용할 반투명도 (0=완전투명, 1=불투명) — 기획자가 클래스 디폴트에서 조절
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DraggedSlotOpacity = 0.5f;

	// 보유 카드 초기 적재 - 레거시 예정 (캐릭터별 컨테이너로 이관 예정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck")
	TObjectPtr<UDataTable> CardSourceTable;

	// 스탯→스테이터스 변환 계수 행렬 테이블 (FCL_StatStatusCoeffRow) — 기획자가 지정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck")
	TObjectPtr<UDataTable> StatStatusCoeffTable;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> EquippedCardSlots;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTileView> OwnedCardSlots;

	// 캐릭터 스테이터스(최종 파생값) 고정 슬롯 — "캐릭터 스테이터스" 영역에 배치
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> AttackText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> DefenseText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> HealthText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> AccuracyText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> EvasionText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> CostText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> BlockText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UImage> SelectedCharacterImage;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UVerticalBox> EquipEffectBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deck")
	TSubclassOf<UCL_StatEffectRow> StatEffectRowClass;

private:
	UFUNCTION()
	void HandleDeckChanged();

	UFUNCTION()
	void HandleDragFinished(UDragDropOperation* Operation);

	void RestoreFadedEntry();

	void RefreshAll();
	void RefreshTileView(UTileView* TileView, bool bEquipped);
	void RefreshStats();

	void RefreshEquippedEffects();

	// 스테이터스 값 표시 포맷
	static FString FormatStatusValue(float Value, bool bPercent);

	UCL_CardSubsystem* GetCardSubsystem() const;

	UPROPERTY()
	int32 SelectedCharIndex = 0;

	// 드래그 중 반투명 처리한 원본 엔트리
	TWeakObjectPtr<UCL_CardEntryWidget> FadedEntry;
};
