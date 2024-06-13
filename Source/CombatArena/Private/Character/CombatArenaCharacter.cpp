// Copyright Luis Infante


#include "Character/CombatArenaCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/CombatArenaPlayerState.h"
#include "AbilitySystem/CombatAbilitySystemComponent.h"
#include "AbilitySystem/CombatArenaAttributeSet.h"
#include "Player/CombatArenaPlayerController.h"
#include "UI/HUD/CombatArenaHUD.h"
#include "Weapons/WeaponBase.h"

ACombatArenaCharacter::ACombatArenaCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	m_OverheadWidget = CreateDefaultSubobject<UWidgetComponent>("OverheadWidget");
	m_OverheadWidget->SetupAttachment(RootComponent);
}

void ACombatArenaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACombatArenaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// If we are on the Server
	InitAbilityActorInfo();
}

void ACombatArenaCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Only Replicating when Weapon is Overlapped
	DOREPLIFETIME_CONDITION(ACombatArenaCharacter, m_OverlappedWeapon, COND_OwnerOnly);
}

void ACombatArenaCharacter::SetOverlappedWeapon(const TObjectPtr<AWeaponBase>& Weapon)
{
	// If we have ended overlap (Holding a pointer to a previous weapon)
	if (m_OverlappedWeapon)
	{
		m_OverlappedWeapon->ShowPickupWidget(false);
	}

	// Set new Overlapped Weapon
	m_OverlappedWeapon = Weapon;
	
	// If we are the Player controlling the server
	if (IsLocallyControlled())
	{
		if (m_OverlappedWeapon)
		{
			m_OverlappedWeapon->ShowPickupWidget(true);
		}
	}
}

void ACombatArenaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatArenaCharacter::InitAbilityActorInfo()
{
	m_PlayerState = GetPlayerState<ACombatArenaPlayerState>();
	if (m_PlayerState)
	{
		// Set ASC
		AbilitySystemComponent = Cast<UCombatAbilitySystemComponent>(m_PlayerState->GetAbilitySystemComponent());

		// Ability System exists on the Player State, Player Controlled Character is the Avatar
		m_PlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(m_PlayerState, this);
			
		// Set AS 
		AttributeSet = Cast<UCombatArenaAttributeSet>(m_PlayerState->GetAttributeSet());
	}
	
	// Set the Widget Controller on the HUD
	m_PlayerController = Cast<ACombatArenaPlayerController>(GetController());
	if (m_PlayerController)
	{
		m_PlayerHUD = Cast<ACombatArenaHUD>(m_PlayerController->GetHUD());
		if (m_PlayerHUD)
		{
			m_PlayerHUD->InitOverlay(m_PlayerController, m_PlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

void ACombatArenaCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// If we are on the Client
	InitAbilityActorInfo();
}

void ACombatArenaCharacter::OnRep_OverlappedWeapon(AWeaponBase* LastOverlappedWeapon) const
{
	// Started Overlap
	if (m_OverlappedWeapon)
	{
		m_OverlappedWeapon->ShowPickupWidget(true);
	}

	// Ended Overlap
	if (LastOverlappedWeapon)
	{
		LastOverlappedWeapon->ShowPickupWidget(false);
	}
}
