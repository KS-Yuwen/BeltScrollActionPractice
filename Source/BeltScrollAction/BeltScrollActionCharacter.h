// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "BeltScrollActionCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UAnimMontage;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ABeltScrollActionCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Enables one extra jump while airborne. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Jump")
	bool bCanDoubleJump = false;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* AttackAction;

	/** Montage played for the normal attack */
	UPROPERTY(EditDefaultsOnly, Category="Combat|Attack")
	UAnimMontage* AttackMontage;

	/** Distance of the attack hit check in front of the character */
	UPROPERTY(EditDefaultsOnly, Category="Combat|Attack", meta=(ClampMin="0.0", Units= "cm"))
	float AttackTraceDistance = 120.0f;

	/** Radius of the attack hit check */
	UPROPERTY(EditDefaultsOnly, Category="Combat|Attack", meta=(ClampMin="0.0", Units= "cm"))
	float AttackTraceRadius = 60.0f;

	/** True while the attack montage is playing */
	bool bIsAttacking = false;

	/** Delegate called when the normal attack montage ends */
	FOnMontageEnded AttackMontageEndedDelegate;

public:

	/** Constructor */
	ABeltScrollActionCharacter();

protected:

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called by ACharacter after each successful jump */
	virtual void OnJumped_Implementation() override;
	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called in Blueprint when character performs its second jump */
	UFUNCTION(BlueprintImplementableEvent, Category="Jump")
	void BP_OnDoubleJump();

	/** Resets the attack state when the montage finishes */
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	/** Starts a normal attack if attack is not already playing */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAttack();

	/** Checks for targets insidle the normal attack hit area */
	UFUNCTION(BlueprintCallable, Category="Combat|Attack")
	void DoAttackTrace();
public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

