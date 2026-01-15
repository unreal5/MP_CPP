// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MP_MultiplayerUtils.generated.h"

/**
 * 
 */
UCLASS()
class MP_CPP_API UMP_MultiplayerUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static void PrintLocalNetRole(AActor* InActor);
	
	UFUNCTION(BlueprintCallable)
	static void PrintRemoteNetRole(AActor* InActor);
};
