// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_MultiplayerUtils.h"

void UMP_MultiplayerUtils::PrintLocalNetRole(AActor* InActor)
{
	FString Msg = "[" + InActor->GetActorLabel() + "] ";
	Msg += InActor->HasAuthority() ? TEXT("Actor has Authority") : TEXT("Actor DOES NOT has Authority");
	const ENetRole LocalRole = InActor->GetLocalRole();
	switch (LocalRole)
	{
	case ROLE_Authority:
		Msg += TEXT(" | Local Role: Authority");
		break;
	case ROLE_AutonomousProxy:
		Msg += TEXT(" | Local Role: Autonomous Proxy");
		break;
	case ROLE_SimulatedProxy:
		Msg += TEXT(" | Local Role: Simulated Proxy");
		break;
	default:
		Msg += TEXT(" | Local Role: NONE");
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
}

void UMP_MultiplayerUtils::PrintRemoteNetRole(AActor* InActor)
{
	FString Msg = "[" + InActor->GetActorLabel() + "] ";
	Msg += InActor->HasAuthority() ? TEXT("Actor has Authority") : TEXT("Actor DOES NOT has Authority");
	const ENetRole LocalRole = InActor->GetRemoteRole();
	switch (LocalRole)
	{
	case ROLE_Authority:
		Msg += TEXT(" | 远端角色: Authority");
		break;
	case ROLE_AutonomousProxy:
		Msg += TEXT(" | 远端角色: Autonomous Proxy");
		break;
	case ROLE_SimulatedProxy:
		Msg += TEXT(" | 远端角色: Simulated Proxy");
		break;
	default:
		Msg += TEXT(" | 远端角色: NONE");
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
}
