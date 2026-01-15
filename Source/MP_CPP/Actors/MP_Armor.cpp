// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_Armor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"


// Sets default values
AMP_Armor::AMP_Armor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// demo
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root")));
	// Create Sphere Mesh
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Mesh"));
	SphereMesh->SetupAttachment(RootComponent);
	// Create Sphere Collision
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMP_Armor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMP_Armor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMP_Armor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (!HasAuthority()) return;

	// AttachToActor只挂接到OtherActor的根组件上，而Character的根组件是CapsuleComponent，不是我们想要的Mesh组件
	//AttachToActor(OtherActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "ArmorSocket");
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character) return;
	SphereMesh->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
	                              "ArmorSocket");
}
