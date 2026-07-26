// Copyright Epic Games, Inc. All Rights Reserved.

#include "BeltScrollActionCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "BeltScrollAction.h"

void ABeltScrollActionCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ACharacter handles the actual double-jump behavior.
	JumpMaxCount = bCanDoubleJump ? 2 : 1;
}

void ABeltScrollActionCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();

	// JumpCurrentCount is 2 only when the second jump succeeds.
	if (bCanDoubleJump && JumpCurrentCount == 2)
	{
		BP_OnDoubleJump();
	}
}

ABeltScrollActionCharacter::ABeltScrollActionCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	// Jump feel
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->GravityScale = 1.6f;
	GetCharacterMovement()->AirControl = 0.6f;

	// Hold the jump button for a slightly higher jump
	JumpMaxCount = 1;
	JumpMaxHoldTime = 0.18f;

	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a fixed-view camera boom.  Absolute rotation keeps the view from
	// turning when the character changes direction.
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1200.0f;
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetRelativeRotation(FRotator(-12.0f, -90.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ABeltScrollActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABeltScrollActionCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ABeltScrollActionCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABeltScrollActionCharacter::Look);
	}
	else
	{
		UE_LOG(LogBeltScrollAction, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABeltScrollActionCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, -MovementVector.Y);
}

void ABeltScrollActionCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ABeltScrollActionCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// A / D: 画面の左右（ワールド X 軸）
		// W / S: 画面の奥・手前（ワールド Y 軸）
		AddMovementInput(FVector::ForwardVector, Right);
		AddMovementInput(FVector::RightVector, Forward);
	}
}

void ABeltScrollActionCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ABeltScrollActionCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ABeltScrollActionCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}
