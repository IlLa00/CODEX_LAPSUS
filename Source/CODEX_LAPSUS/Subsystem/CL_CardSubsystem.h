// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/FCL_CardStatBlock.h"
#include "CL_CardSubsystem.generated.h"

class UCL_CardInstance;
class UDataTable;

// 보유 카드 한 종류 + 수량
USTRUCT(BlueprintType)
struct FCL_OwnedCard
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	TObjectPtr<UCL_CardInstance> Card = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Card")
	int32 Amount = 0;
};

// 캐릭터 한 명의 장착 세트
USTRUCT()
struct FCL_EquippedSet
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<UCL_CardInstance>> Cards;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCL_OnDeckChanged);

UCLASS()
class CODEX_LAPSUS_API UCL_CardSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// DataTable의 모든 행을 보유 카드로 적재 (Amount 1씩, 같은 CardID는 누적)
	UFUNCTION(BlueprintCallable, Category = "Card")
	void InitOwnedFromDataTable(UDataTable* Table);

	// 보유 카드 1장 추가 (같은 CardID면 Amount 누적)
	UFUNCTION(BlueprintCallable, Category = "Card")
	void AddOwnedCard(UCL_CardInstance* Card, int32 Count = 1);

	// 장착: 슬롯 한도 & 보유 수량 확인 후 Owned에서 차감하여 해당 캐릭터 세트에 추가
	UFUNCTION(BlueprintCallable, Category = "Card")
	bool EquipCard(int32 CharIndex, UCL_CardInstance* Card, int32 MaxEquipSlots);

	// 장착 해제: 세트에서 제거하고 Owned Amount 복귀
	UFUNCTION(BlueprintCallable, Category = "Card")
	bool UnequipCard(int32 CharIndex, UCL_CardInstance* Card);

	// 장착 카드 스탯 합산
	UFUNCTION(BlueprintCallable, Category = "Card")
	FCL_CardStatBlock GetEquippedStatTotal(int32 CharIndex) const;

	// C++ 전용 (const 참조 반환이라 UFUNCTION 비노출)
	const TArray<FCL_OwnedCard>& GetOwnedCards() const { return OwnedCards; }

	UFUNCTION(BlueprintCallable, Category = "Card")
	TArray<UCL_CardInstance*> GetEquippedCards(int32 CharIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Card")
	int32 GetEquippedCount(int32 CharIndex) const;

	UPROPERTY(BlueprintAssignable, Category = "Card")
	FCL_OnDeckChanged OnDeckChanged;

private:
	// 보유 Amount를 1 늘림 (없으면 새 항목, 0 이하가 되면 제거)
	void ChangeOwnedAmount(UCL_CardInstance* Card, int32 Delta);

	UPROPERTY()
	TArray<FCL_OwnedCard> OwnedCards;

	UPROPERTY()
	TMap<int32, FCL_EquippedSet> EquippedByCharacter;
};
