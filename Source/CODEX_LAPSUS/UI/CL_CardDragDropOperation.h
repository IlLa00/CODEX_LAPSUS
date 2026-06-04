// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Header/CL_Define.h"
#include "CL_CardDragDropOperation.generated.h"

class UCL_CardInstance;
class UCL_CardEntryWidget;

UCLASS()
class CODEX_LAPSUS_API UCL_CardDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Card")
	TObjectPtr<UCL_CardInstance> Card = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Card")
	ECL_CardZone SourceZone = ECL_CardZone::Owned;

	UPROPERTY(BlueprintReadWrite, Category = "Card")
	int32 SourceCharIndex = 0;

	// 드래그를 시작한 원본 엔트리 위젯 (리스트에 그대로 남아있음).
	// 드래그 중 원본 슬롯을 반투명 처리/복원할 때 참조한다.
	UPROPERTY(BlueprintReadWrite, Category = "Card")
	TObjectPtr<UCL_CardEntryWidget> SourceEntry = nullptr;
};
