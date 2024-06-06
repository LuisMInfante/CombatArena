// Copyright Luis Infante


#include "Character/CombatArenaCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/CombatArenaPlayerController.h"

ACombatArenaCharacter::ACombatArenaCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	m_CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	m_CameraBoom->SetupAttachment(GetMesh());
	m_CameraBoom->TargetArmLength = 100.0f;
	m_CameraBoom->bUsePawnControlRotation = true;

	m_Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	m_Camera->SetupAttachment(m_CameraBoom, USpringArmComponent::SocketName);
	m_Camera->bUsePawnControlRotation = false;

	m_CharacterMovement = GetCharacterMovement();
	bUseControllerRotationYaw = false;
	m_CharacterMovement->bOrientRotationToMovement = true;
}

void ACombatArenaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACombatArenaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACombatArenaCharacter::BeginPlay()
{
	Super::BeginPlay();
}
