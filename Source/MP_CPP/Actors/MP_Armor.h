// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_Armor.generated.h"

UCLASS()
class MP_CPP_API AMP_Armor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMP_Armor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> SphereMesh;
	UPROPERTY()
	TObjectPtr<class USphereComponent> SphereCollision;
};
