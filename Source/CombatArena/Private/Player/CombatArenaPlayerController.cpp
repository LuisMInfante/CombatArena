// Copyright Luis Infante


#include "Player/CombatArenaPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

ACombatArenaPlayerController::ACombatArenaPlayerController()
{
	bReplicates = true;
}

void ACombatArenaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Get Owner Pawn
	m_ControlledCharacter = GetPawn<ACharacter>();
	
	// Assert the mapping context is valid
	check(m_CombatArenaContext);

	// Initialize Input
	m_Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(m_Subsystem);
	m_Subsystem->AddMappingContext(m_CombatArenaContext, 0);
	
}

void ACombatArenaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	m_EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	m_EnhancedInputComponent->BindAction(m_MoveAction,
										ETriggerEvent::Triggered,
										this,
										&ACombatArenaPlayerController::Move
										);
	m_EnhancedInputComponent->BindAction(m_LookAction,
									ETriggerEvent::Triggered,
									this,
									&ACombatArenaPlayerController::Look
									);
	m_EnhancedInputComponent->BindAction(m_JumpAction,
									ETriggerEvent::Triggered,
									this,
									&ACombatArenaPlayerController::Jump
									);
}

void ACombatArenaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVec2 = InputActionValue.Get<FVector2D>();
	/* Rotation from Camera to Character, Flattened and Pointing in X/Y direction */
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if(m_ControlledCharacter)
	{
		m_ControlledCharacter->AddMovementInput(ForwardVector, InputAxisVec2.Y);
		m_ControlledCharacter->AddMovementInput(RightVector, InputAxisVec2.X);
	}
}

void ACombatArenaPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVec2 = InputActionValue.Get<FVector2D>();
	
	if(m_ControlledCharacter)
	{
		m_ControlledCharacter->AddControllerPitchInput(InputAxisVec2.Y);
		m_ControlledCharacter->AddControllerYawInput(InputAxisVec2.X);
	}
}

void ACombatArenaPlayerController::Jump()
{
	if(m_ControlledCharacter)
	{
		m_ControlledCharacter->Jump();
	}
}
