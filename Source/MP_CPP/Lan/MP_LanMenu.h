// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MP_LanMenu.generated.h"

class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class MP_CPP_API UMP_LanMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UEditableTextBox> TextBox_IPAddress;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Button_Host;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Button_Join;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> HostingLevel;
	
	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();

	

};
