// Copyright Epic Games, Inc. All Rights Reserved.

#include "Research3DPlatformerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DestroyableObject.h"


//////////////////////////////////////////////////////////////////////////
// AResearch3DPlatformerCharacter

AResearch3DPlatformerCharacter::AResearch3DPlatformerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// Set starting coins
	Keys = 0;

	// Set starting keys
	Coins = 0;

	// Set starting lives
	Lives = 3;

	// Set initial dash
	CanDash = true;

	// Set initial dash energy
	DashEnergy = 1200.0;

	// Set initial dash energy
	MaxDashEnergy = 1200.0;

	// Set initial attack state
	IsAttacking = false;

	// Set initial checkpoint
	Checkpoint = 0;

	// Set initial milliseconds
	Milliseconds = 0;

	// Set initial seconds
	Seconds = 0;

	// Set initial minutes
	Minutes = 0;

	// Set initial start timer
	StartTimer = false;

	// Set initial on ladder
	OnLadder = false;

	// Set initial Unlimited Dash Energy
	UnlimitedDashEnergy = false;

	PrimaryActorTick.bCanEverTick = true;
}

void AResearch3DPlatformerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AResearch3DPlatformerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AResearch3DPlatformerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AResearch3DPlatformerCharacter::Look);

		//Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &AResearch3DPlatformerCharacter::StartDash);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &AResearch3DPlatformerCharacter::EndDash);

		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AResearch3DPlatformerCharacter::StartAttack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AResearch3DPlatformerCharacter::EndAttack);

	}

}

void AResearch3DPlatformerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AResearch3DPlatformerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

// Make character dash
void AResearch3DPlatformerCharacter::StartDash()
{
	if (UnlimitedDashEnergy == true && CanDash == true)
	{
		FRotator PlayerDirection = GetActorRotation();
		FVector PlayerLocation = GetActorForwardVector();
		LaunchCharacter(PlayerLocation * DashEnergy, 0, false);
		CanDash = false;
	}
	else if (CanDash == true)
	{
		FRotator PlayerDirection = GetActorRotation();
		FVector PlayerLocation = GetActorForwardVector();
		LaunchCharacter(PlayerLocation * DashEnergy, 0, false);
		CanDash = false;
		DashEnergy = 0;
	}
}

// Stop character dash
void AResearch3DPlatformerCharacter::EndDash()
{
	CanDash = true;
}

void AResearch3DPlatformerCharacter::StartAttack()
{

	IsAttacking = true;
}

void AResearch3DPlatformerCharacter::EndAttack()
{
	IsAttacking = false;
}

// On every frame
void AResearch3DPlatformerCharacter::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

	if (CanDash == true && DashEnergy < 1200)
	{
		DashEnergy += 10.0;
	}

	if (StartTimer == true)
	{
		Timer();
	}

	if (OnLadder == true)
	{
		LaunchCharacter(FVector(0, 0, 400), false, true);
	}
}

// Timer - on milliseconds equal to 60 increamnt second, if seconds equal 60, incremeant minutes
void AResearch3DPlatformerCharacter::Timer()
{
	if (Seconds == 60)
	{
		Minutes += 1;
		Seconds = 0;
	}
	else if (Milliseconds == 60)
	{
		Seconds += 1;
		Milliseconds = 0;
	}
	else
	{
		Milliseconds += 2;
	}
}

// on collecting energy item, set energy to near full
void AResearch3DPlatformerCharacter::GainEnergy()
{
	DashEnergy = 1150;
}

// Force character to jump
void AResearch3DPlatformerCharacter::ForceJump()
{
	LaunchCharacter(FVector(0,0,1000),false, true);
}

// Lose a life
void AResearch3DPlatformerCharacter::LoseLife()
{
	Lives -= 1;
	if (Lives == 0)
	{
		Destroy();
	}
}

// Gain a life
void AResearch3DPlatformerCharacter::GainLife()
{
	Lives += 1;
}

// Gain a coin
void AResearch3DPlatformerCharacter::GainCoin()
{
	Coins += 1;
}

// Gain a key
void AResearch3DPlatformerCharacter::GainKey()
{
	Keys += 1;
}




