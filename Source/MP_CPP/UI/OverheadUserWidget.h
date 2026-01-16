// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MP_CPP_API UOverheadUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* ArmorValueText;
};
