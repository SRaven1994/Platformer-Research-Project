// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Research3DPlatformerCharacter.generated.h"



UCLASS(config=Game)
class AResearch3DPlatformerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	// Dash Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	// Attack Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	// Create lives
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	int Lives;

	// Create coins
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	int Coins;

	//Create keys
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	int Keys;

	// Create Dash Energy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	float DashEnergy;

	// Create Max Dash Energy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	float MaxDashEnergy;

	// Create Can Dash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	bool CanDash;

	// Create Player Attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	bool IsAttacking;

	// Create Player checkpoint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	int Checkpoint;

	

public:
	AResearch3DPlatformerCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// Create dash functions
	void StartDash();

	void EndDash();


			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	
	// Called every frame
	UFUNCTION(BlueprintCallable)
	virtual void Tick(float DeltaTime);
	


	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Create force character jump function
	void ForceJump();

	// Create lose life function
	void LoseLife();

	// Create gain life function
	void GainLife();

	// Create gain coin function
	void GainCoin();

	// Create gain key function
	void GainKey();

	// Create attack functions
	void StartAttack();

	void EndAttack();

};

