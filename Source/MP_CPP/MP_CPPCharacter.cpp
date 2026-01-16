#include "MP_CPPCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MP_CPP.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "UI/OverheadUserWidget.h"

AMP_CPPCharacter::AMP_CPPCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	OverheadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidgetComponent"));
	OverheadWidgetComponent->SetupAttachment(RootComponent);
	OverheadWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	OverheadWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
}

void AMP_CPPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogMP_CPP, Error, TEXT( "'%s' " ), *GetNameSafe(this));
		return;
	}

	auto JumpActionLambda = [this](auto, bool IsJumping)
	{
		IsJumping ? Jump() : StopJumping();
	};
	EnhancedInputComponent->BindActionValueLambda(JumpAction, ETriggerEvent::Started, JumpActionLambda, true);
	EnhancedInputComponent->BindActionValueLambda(JumpAction, ETriggerEvent::Completed, JumpActionLambda, false);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMP_CPPCharacter::Move);
	EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMP_CPPCharacter::Look);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMP_CPPCharacter::Look);
}

void AMP_CPPCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void AMP_CPPCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AMP_CPPCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AMP_CPPCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AMP_CPPCharacter::DoJumpStart()
{
	Jump();
}

void AMP_CPPCharacter::DoJumpEnd()
{
	StopJumping();
}

USkeletalMeshComponent* AMP_CPPCharacter::GetMeshComponent_Implementation()
{
	return GetMesh();
}

void AMP_CPPCharacter::GrantArmor_Implementation(int32 ArmorAmount)
{
	Armor += ArmorAmount;
	// 自身也需要更新
	OnRep_Armor(Armor);
}

void AMP_CPPCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, Armor);
}

void AMP_CPPCharacter::OnRep_Armor(int32 OldArmor)
{
	auto Overhead = Cast<UOverheadUserWidget>(OverheadWidgetComponent->GetWidget());

	if (!IsValid(Overhead)) return;

	FString ArmorString = FString::Printf(TEXT("护甲值：%d"), Armor);
	Overhead->ArmorValueText->SetText(FText::FromString(ArmorString));
}
