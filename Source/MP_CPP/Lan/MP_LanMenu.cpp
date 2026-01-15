// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_LanMenu.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void UMP_LanMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Bind button click events
	if (Button_Host)
	{
		Button_Host->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	if (Button_Join)
	{
		Button_Join->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}

	GetOwningPlayer()->SetInputMode(FInputModeUIOnly{});
	GetOwningPlayer()->SetShowMouseCursor(true);
}

void UMP_LanMenu::HostButtonClicked()
{
	FInputModeGameOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->SetShowMouseCursor(false);

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, HostingLevel, true, "listen");
}

void UMP_LanMenu::JoinButtonClicked()
{
	FInputModeGameOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->SetShowMouseCursor(false);

	const FString IPAddress = TextBox_IPAddress ? TextBox_IPAddress->GetText().ToString() : FString();
	UGameplayStatics::OpenLevel(this, *IPAddress);
}
